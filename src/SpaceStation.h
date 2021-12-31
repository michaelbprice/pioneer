// Copyright © 2008-2022 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _SPACESTATION_H
#define _SPACESTATION_H

#include "ModelBody.h"
#include "Quaternion.h"
#include "SpaceStationType.h"

#define MAX_DOCKING_PORTS 240 //256-(0x10), 0x10 is used because the collision surfaces use it as an identifying flag

class Body;
class Camera;
class CityOnPlanet;
class Frame;
class NavLights;
class Ship;
class Space;
class SystemBody;

namespace Graphics {
	class Renderer;
}

namespace SceneGraph {
	class Animation;
}

class SpaceStation : public ModelBody {
public:
	OBJDEF(SpaceStation, ModelBody, SPACESTATION);
	static void Init();

	enum class DockingRefusedReason { // <enum scope='SpaceStation::DockingRefusedReason' name='DockingRefusedReason' public>
		ClearanceAlreadyGranted,
		TooFarFromStation,
		NoBaysAvailable
	};

	SpaceStation() = delete;
	// Should point to SystemBody in Pi::currentSystem
	SpaceStation(const SystemBody *);
	SpaceStation(const Json &jsonObj, Space *space);

	virtual ~SpaceStation();
	virtual vector3d GetAngVelocity() const { return vector3d(0, m_type->AngVel(), 0); }
	virtual bool OnCollision(Body *b, Uint32 flags, double relVel) override;
	bool DoShipDamage(Ship *s, Uint32 flags, double relVel);
	virtual void Render(Graphics::Renderer *r, const Camera *camera, const vector3d &viewCoords, const matrix4x4d &viewTransform) override;
	virtual void StaticUpdate(const float timeStep) override;
	virtual void TimeStepUpdate(const float timeStep) override;

	virtual const SystemBody *GetSystemBody() const override { return m_sbody; }
	virtual void PostLoadFixup(Space *space) override;
	virtual void NotifyRemoved(const Body *const removedBody) override;

	virtual void SetLabel(const std::string &label) override;

	// should call Ship::Undock and Ship::SetDockedWith instead
	// Returns true on success, false if permission denied
	bool LaunchShip(Ship *ship, const int port);
	void SetDocked(Ship *ship, const int port);
	void SwapDockedShipsPort(const int oldPort, const int newPort);

	int GetNearbyTraffic(double radius);

	bool GetDockingClearance(Ship *s);
	int GetDockingPortCount() const { return m_type->NumDockingPorts(); }
	int GetFreeDockingPort(const Ship *s) const; // returns -1 if none free
	int GetMyDockingPort(const Ship *s) const;
	int NumShipsDocked() const;

	const SpaceStationType *GetStationType() const { return m_type; }
	bool IsGroundStation() const;

	bool AllocateStaticSlot(int &slot);

	// use docking bay position, if player has been granted permission
	vector3d GetTargetIndicatorPosition() const override;

	// need this now because stations rotate in their frame
	virtual void UpdateInterpTransform(double alpha) override;

protected:
	virtual void SaveToJson(Json &jsonObj, Space *space) override;

private:
	void DockingUpdate(const double timeStep);
	void PositionDockingShip(Ship *ship, int port) const;
	void PositionDockedShip(Ship *ship, int port) const;
	bool LevelShip(Ship *ship, int port, const float timeStep) const;
	void DoLawAndOrder(const double timeStep);
	bool IsPortLocked(const int bay) const;
	void LockPort(const int bay, const bool lockIt);

	/* Stage 0 means docking port empty
	 * Stage 1 means docking clearance granted to ->ship
	 * Stage 2 to m_type->numDockingStages is docking animation
	 * Stage m_type->numDockingStages+1 means evaluating repos
	 * Stage m_type->numDockingStages+2 means ship is repositioning
	 * Stage m_type->numDockingStages+3 means ship is just docked
	 * Stage m_type->numDockingStages+4 means ship is docked
	 * Stage -1 to -m_type->numUndockStages is undocking animation
	 */
	struct shipDocking_t {
		shipDocking_t() :
			ship(0),
			shipIndex(0),
			stage(0),
			stagePos(0),
			fromPos(0.0),
			fromRot(1.0, 0.0, 0.0, 0.0),
			maxOffset(0)
		{}

		Ship *ship;
		int shipIndex; // deserialisation
		int stage;
		double stagePos;  // 0 -> 1.0
		vector3d fromPos; // in station model coords
		Quaterniond fromRot;
		double maxOffset;
	};
	typedef std::vector<shipDocking_t>::const_iterator constShipDockingIter;
	typedef std::vector<shipDocking_t>::iterator shipDockingIter;
	std::vector<shipDocking_t> m_shipDocking;

	SpaceStationType::TPorts m_ports;

	double m_oldAngDisplacement;

	void InitStation();
	const SpaceStationType *m_type;
	const SystemBody *m_sbody;
	CityOnPlanet *m_adjacentCity;
	enum { NUM_STATIC_SLOTS = 4 };
	bool m_staticSlot[NUM_STATIC_SLOTS];

	SceneGraph::Animation *m_doorAnimation;
	double m_doorAnimationStep;
	double m_doorAnimationState;

	std::unique_ptr<NavLights> m_navLights;
};

#endif /* _SPACESTATION_H */
