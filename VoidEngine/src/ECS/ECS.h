#pragma once
#include <cstdint>
#include <vector>
#include <unordered_map>

// Type of ID
typedef std::uint64_t IDType;

// Type of entityID and ComponentTypeID
typedef IDType EntityID;
typedef IDType ComponentTypeID;

// Null entity
const IDType NULL_ENTITY = 0;


// ID of archetype
typedef std::vector<ComponentTypeID> ArchetypeID;


#pragma region Component
// Create ID generator template
template<class T>
class TypeIDGenerator
{
private:
	// m_count will be different between classes:
	// TypeIDGenerator<Component>::m_count is different than
	// TypeIDGenerator<Entity>::m_count
	static IDType m_count;

public:
	template <class U>
	static const IDType GetNewID()
	{
		/*
		idCounter is a static copy of the
		For each T instatiation, a new set of IDs can be
		generated for each subsequent U.
		The same T and U will always provide the same IDType.
		*/
		static const IDType idCounter = m_count++;
		return idCounter;
	}
};

// Initialize the template id
template<class T> IDType TypeIDGenerator<T>::m_count = 0;

class ComponentBase
{
public:
	virtual ~ComponentBase() {}

	virtual void DestroyData(unsigned char* data) const = 0;
	virtual void MoveData(unsigned char* source, unsigned char* destination) const = 0;
	virtual void ConstructData(unsigned char* data) const = 0;

	virtual std::size_t GetSize() const = 0;
};

template<class C>
class Component : public ComponentBase
{
public:
	virtual void DestroyData(unsigned char* data) const override;
	virtual void MoveData(unsigned char* source, unsigned char* destination) const override;
	virtual void ConstructData(unsigned char* data) const override;

	virtual std::size_t GetSize() const override;

	static ComponentTypeID GetTypeID();
};

// Handling the memory:

template<class C>
void Component<C>::DestroyData(unsigned char* data) const
{
	// Obtains a pointer to the object located at the address represented in parentheses
	C* dataLocation = std::launder(reinterpret_cast<C*>(data));

	dataLocation->~C();
}

template<class C>
void Component<C>::ConstructData(unsigned char* data) const
{
	new (&data[0]) C();
}

template<class C>
void Component<C>::MoveData(unsigned char* source, unsigned char* destination) const
{
	new (&destination[0]) C(std::move(*reinterpret_cast<C*>(source)))
}

template<class C>
std::size_t Component<C>::GetSize() const
{
	return sizeof(C);
}

template<class C>
ComponentTypeID Component<C>::GetTypeID()
{
	return TypeIDGenerator<ComponentBase>::GetNewID();
}

// End Handling the memory
#pragma endregion

#pragma region Entity
class Entity
{
private:
	EntityID m_id;
	ECS& m_ecs;

public:
	explicit Entity(ECS& ecs) : m_id(ecs.GetNewId()), m_ecs(ecs)
	{
		m_ecs.RegisterEntity(m_id);
	}

	template<class C, typename... Args>
	C* AddComponent(Args&&... args)
	{
		return m_ecs.AddComponent<C>(m_id, std::forward<Args>(args)...);
	}

	template<class C>
	C* AddComponent(C&& c)
	{
		return m_ecs.AddComponent<C>(m_id, std::forward<C>(c));
	}

	EntityID GetID() const
	{
		return m_id;
	}
};
#pragma endregion

#pragma region Archetype
typedef unsigned char* ComponentData;

struct Archetype
{
	ArchetypeID type;
	std::vector<ComponentData> componentData;
	std::vector<EntityID> entityIDs;
	std::vector<std::size_t> componentDataSize;
};
#pragma endregion

#pragma region ECS
class ECS
{
private:
	typedef std::unordered_map<ComponentTypeID, ComponentBase*> ComponentTypeIDBaseMap;

	struct Record
	{
		Archetype* archetype;
		// index in the archetype array
		std::size_t index;
	};

	typedef std::unordered_map<EntityID, Record> EntityArchetypeMap;

	typedef std::vector<Archetype*> ArchetypesArray;

	typedef std::unordered_map<std::uint8_t, std::vector<SystemBase*>>
		SystemsArrayMap;


	EntityArchetypeMap m_entityArchetypeMap;
	ArchetypesArray m_archetypes;
	EntityID m_entityIDCounter;
	SystemsArrayMap m_systems;
	ComponentTypeIDBaseMap m_componentMap;

public:
	ECS();
	~ECS();

	EntityID GetNewID();

	template<class C>
	void RegisterComponent();

	template<class C>
	bool isComponentRegistered();

	void RegisterSystem(const std::uint8_t& layer, SystemBase* system);

	void RegisterEntity(const EntityID entityID);

	void RunSystems(const std::uint8_t& layer, const float elapsedMilliseconds);

	Archetype* GetArchetype(const ArchetypeID& id);

	template<class C, typename... Args>
	C* AddComponent(const EntityID& entityID, Args&&... args);

	template<class C>
	void RemoveComponent(const EntityID& entityID);

	template<class C>
	C* GetComponent(const EntityID& entityID);

	template<class C>
	bool HasComponent(const EntityID& entityID);

	void RemoveEntity(const EntityID& entityID);

	template<class... Cs>
	std::vector<EntityID> GetEntitiesWith();
};
#pragma endregion


/*
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentId = std::size_t;

inline ComponentId getComponentTypeId()
{
	static ComponentId lastId = 0;
	return lastId++;
}

template <typename T> inline ComponentId getComponentTypeId() noexcept
{
	static ComponentId typeId = getComponentTypeId();
	return typeId;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;
	virtual void Init() {}
	virtual void Update() {}
	virtual void Draw() {}

	virtual ~Component() {}
};

class Entity
{
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

public:
	void update()
	{
		for (auto& c : components) c->Update();
	}

	void draw()
	{
		for (auto& c : components) c->Draw();
	}

	bool isActive() const { return active; }
	void destroy() { active = false; }

	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeId<T>()];
	}

	template <typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeId<T>()] = c;
		componentBitSet[getComponentTypeId<T>()] = true;

		c->Init();
		return *c;
	}

	template <typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeId<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void update()
	{
		for (auto& e : entities) e->update();
	}

	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	void refresh()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	Entity& addEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};
*/
