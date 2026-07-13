The Guns Dungeons, a 8-bit stylized rogueelike descendant of The Guns. Now with dynamic sub-step division matrix!

Funny, I discovered the name "sub-step division matrix" after I actually made all those three games lol

(and still not sure it's called that way, feel free to correct me)

========================================================================

NO AI CODE GENERATION WAS USED IN THESE PROJECTS WHATSOEVER

NO ALGORITHMS WERE COPIED OR REVERSE ENGINEERED

ALL DONE IN BARE C++ EXCEPT DISPLAYING SPRITES AND MANAGING WINDOWS. SFML WAS USED

========================================================================

TO MAINTAIN ABSOLUTE TRANSPARENCY REGARDING THIS PROJECT'S AUTHENTICITY, THE SOURCE CODE REMAINS EXACTLY AS IT WAS ORIGINALLY WRITTEN:

- ORGANIC STRUCTURAL GROWTH: THE ENTIRE PROJECT IS CONTAINED WITHIN A SINGLE FILE. THE FIRST HALF HANDLES COMPLEX ITEM INITIALIZATION. THE SECOND HALF CONTAINS THE CORE GAME LOGIC ALONG WITH LEGACY CODE BLOCKS INTENTIONALLY RETAINED DURING DEVELOPMENT. VARIABLE NAMING CONVENTIONS VARY, DIRECTLY REFLECTING A SELF-TAUGHT, ORGANIC, EXPERIMENTAL DEVELOPMENT PROCESS.

- LOCAL VERSION CONTROL PROOF: BEFORE ADOPTING STANDARD GIT PRACTICES, MY VERSION CONTROL CONSISTED OF MANUALLY SAVING DISTINCT ITERATIONS INTO SEPARATE LOCAL FOLDERS. GITHUB ACTS STRICTLY AS THE STORAGE AND PUBLISHING DESTINATION FOR THIS COMPLETED FINAL MILESTONE.

- THE VISUAL PROOF: CHECK main.cpp FOR PROOF OF THE AUTHENTICITY. THE LAYOUT, ARCHITECTURE, AND RAW STRUCTURAL EVOLUTION SERVE AS A DIRECT, UNEDITED DIGITAL FINGERPRINT PROVING AUTHENTIC, MANUAL HUMAN DEVELOPMENT.

========================================================================

THE GUNS DUNGEONS (in addition to The Guns mechanics):

- PROCEDURAL GENERATION: a stage is not a map, but rather an array of how many templates of a certain type (e.g. shop, easy room, hard room, etc.) should be in it. When generating a stage, the algorithm picks a room type, picks a random template of this type, and attaches it to a random previously generated room (while checking if it overlaps the existing rooms). All rooms have doors if they connect with other rooms, and the lowest-right room has a door down, taking you to the next stage (triggers when the player touches the specific atoms placed at the border)

- DYNAMIC MAP: even though it's made of static atoms in a static grid, objects can move or be destroyed. Flying platforms check for all entities standing on top of it, and try to move them up by 1 first. If all move, the platform moves up by 1 (rewrites itself 1 pixel higher). The engine is modified the way that checks with negative y speed are ignored, so that any entity can freely jump through the platform, but never fall through it.

- DESTROYABLE OBJECTS: There are objects on the map that take damage only from dynamite (unique throwable, look below). If it's destroyed, an animation is played and all the atoms in it are replaced with air.

- DYNAMIC DOORS: doors are created when the player first enters the room and destroy themselves once there are no enemies.

- 8-WAY SHOOTING: to accommodate the 8-bit arcade game genre, I removed the mouth for aiming. Instead, aiming and shooting is done by arrows. If the weapon is fully auto, it fires when any arrow is pressed. Semi-automatic weapons fire when any arrow is released in the set direction. If a player presses two arrows orthogonal to each other (e.g. up + right), the weapon fires a projectile giving it 1/1,41 velocity and a PI/4 rotation in both directions. The weapon uses distinct animations for diagonal aiming and firing. If idle, the weapon is pointed flat wherever was the last direction of player movement or the last direction it was pointed if the player is still.

- DYNAMITE: A unique explosive that can deal damage to blocks and enemies alike. Affected by gravity. Rotates, unless it has a wall on its side, in which case it's vertical, unless it has a wall under it, in which case it lies or slides flat. Priority order: check floor - check wall - rotation. Emits sparks from where the fuse is visually, even though the hitbox doesn't change.

- SHOP: Some levels don't have enemies. Those have 4 procedurally generated items to buy for flash drives - weapons, health and armor, or unique passive item (e.g. Shotgun Shells gives 2 more projectiles, but less damage per projectile. Formula calculates the total damage to be multiplied by a rigid value). Flash drives are dropped from enemies.

- BOSS 1: And, of course, it features 2 unique bosses. The sentry gun fires slow projectiles and turns very slowly. When its health drops below half, it starts firing twice as fast, turning twice as fast, and dealing twice the damage on direct contact (since it's hot), but overheats and has to cool down. Visual animation for overheating.

- BOSS 2: Mortar. Fires projectiles calculated to hit where you are standing and deal splash damage. When the health drops below half, it starts firing inaccurately(need to check) and a lot faster. Both bosses give good loot.

