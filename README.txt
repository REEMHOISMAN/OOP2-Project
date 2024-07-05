====== OOP2 PROJECT - PAPA LOUIE: WHEN PIZZAS ATTACK =====
names: Re'em Hoisman , Alon Zargari
ids: 2111694146 , 208626515

---- Program info ----
This project is a clone of the game papa louie when pizzas attack, 
The game is based on object-oriented principles and includes design patterns
such as State, Command, Strategy, Factory 
About the game:
-Papa Louie (the main player) has to collect pizzas during the game when he collects
 all the pizzas in the game he can save his friend who is locked in a cage
-In order to collect the pizzas he has to kill a pizza monster that after it dies it turns into a pizza tray
-He has to be careful of the cheese that the pizza monster shoots at him otherwise 
 Papa Louie will be stuck until the space bar is pressed 3 times 
-During the game he must collect coins and avoid
 From clashing with monsters acting according to a certain strategy and finishing the game with a high score
-Papa Louie can collect during the game salt bombs and hearts which will help him pass the stages successfully 
-Use various skills like jumping, running, walking, hovering, attacking, crouching, and climbing ladders to collect
 pizzas and complete the game successfully.
 Follow the in-game instructions to navigate through levels and achieve the highest score. Enjoy and good luck!


---- Files ----

folder Design Patterns:
--------------------------

folder States:
---------------
folder Game States:
-----------------------
GameState-> pure  abstract class 
InGameState-> manage the game events  ,movements of moving objects, perform collision detection, and render game objects.
MenuState-> the menu that showed for the user in the start , the menu hold buttons that each button contain certain command
HelpState-> state to show for the user the Controls screean of the game or the How To Play screen 
GameOverState-> When a player successfully finished the game or he died in one of the stages this state comes into action and displays his score

folder Pizza Enemy States:
PizzaEnemyState->pure  abstract class 
MovingState-> state to manage movment of the pizza enemy ,the moving is follows by strategies 
AttackState-> state to manage the attacking process of the pizza enemy such as insert new cheese weapon to the moving objects list
DieState-> Performs the process of the pizza enemy after collide with bomb 
(turn into pizza tray, push to the list pizza tray and deleting him self from the moving object list)

folder Player States:
-----------------------
PlayerState->base class for the player states
StandState->Papa Louie do nothing so he standing from this state he can move to most states
WalkState-> Papa Louie's walk from this state you cane move to RunState , JumpState , StandState , CheesedState , BombState
RunState-> Papa Louie's run after pressing amount of time on the arrows from this state you can move to:  JumpState , StandState , CheesedState 
JumpState-> Papa Louie's jump , from this state you can move to : DivingState , StandState , BombState , CheesedState
DivingState->Papa Louie's diving this state activate after pressing on spacebar  certain time from this state you can move to : StandState
CheesedState-> Papa Louie is stuck on the ground coverd by cheese after collide withe the cheese weapon affter
			  pressing 3 time on the space bar you can rescue from this situation 
BombState-> Papa Louie's attack , this state manage the proccess of inserting new moving object to the list
CrouchState->the state to pick up a pizza tray or drop them to ground 
ClimbingState-> the state to climbs on ladder that in the game 

folder Factories:
------------------
MovingObjectFactory- factory to creat the most of the moving objects in the game , 
				each moving object register to a map than he been created 
StaticObjectFactory - same as MovingObjectFactory but for the static objects also here 
				  each static object register to a map than he been created 

folder Commands:
---------------------
Command-> pure abstract class
ControlSoundCommand-> response for the mute the music after click the mute button 
SwitchScreenCommand-> response to switch the screens (help screen ,control screen ,Game)
 
folder Strategies:
-------------------
SideToSideStrategy-> moving an object from side to side , direction is changed after collide with wall 
UpDownStrategy-> moving an object up and down 

folder SingleTones:
---------------------
ResourceManager -> manage all the resources of the game (textures, files, sounds) and use them by get an instance off them 
GameCollisions -> update collision map of possible collisions between different objects This class uses a declaration / cpp
			       files (CollisionHandling.h / .cpp) and registers objects to the map with their collision function using multi methods, method 

----GameObjects----

folder GameObjects:
-----------------------
GameObject->base class for all the objects in the game 

folder MovingObjects:
------------------------
MovingObject->base class for the static objects in the game 
Weapon->base class for the weapons  in the game 
Entity->base class for the entities  in the game 
Enemy->base class for the enemies  in the game 
BasicEnemy-> those enemies not attacking but they moving in the game by the strategies
PizzaEnemy-> manage his own states, changing his strategy of movments after amount of jumps loading his die state  
Player-> manage his own states by handle user input also response to his own data like amount of coins and pizzas he had, life,bombs stack and more
Cage-> lifting up after Papa Louie given all pizzas to the fat man 
CheeseBullet->weapon of the pizza enemy , inserted during the game to the moving object list with SideToSideStrategy strategy 
MovingSaltBomb->weapon of Papa Louie , inserted during the game to the moving object list after pressing X button with SideToSideStrategy  
and change the strategy after collide withe the ground to UpDownStrategy  
FatMan->know the amount of pizzas he need to recive from Papa Louie, If he doesn't get the required amount he gets angry else he happy  
Friend-> activate UpDownStrategy after he set free 

folder StaticObject:
---------------------
StaticObject->base class for the static objects in the game 
Coin, Ladder, Heart, Obstacle, StaticSaltBomb, Pizza-> items that Papa Louie can collect during the game

GameController-> manage the states of the game running the game loop 
Level-> response to read the levels from a file named "playlist", place the objects in their places and reading the game levels, holding the objects lists 
Button-> class to represent a button that each button in the game receive a command and position on the screen
CollisionHandling->GameCollisions (the single tone) class use this file this is simple declaration file and his cpp  to implement the functions that declared  
UserInterface-> showing all the game info to the user during the game
Macros-> defining constants for the game, Enum , declare "using's" in the game
main-> the main of the game to run the game 


---- Data base ----
unordered_map<std::string, sf::Texture>m_textures- holds all of the textures in the game
unordered_map<ObjectAnimation, std::vector<sf::IntRect>> m_animations-holds the IntRect of each sprite sheet into vector (animation)
unordered_map<std::string, sf::SoundBuffer> m_sounds -holds all of the sounds in the game
map<Key, HitFunctionPtr> m_collideMap- holding the collision functions and pair<std::type_index, std::type_index>(using Key)- multimethodes
list<std::unique_ptr<MovingObject>> m_movingObjects-holds all the moving objects in the game 
list<std::unique_ptr<StaticObject>> m_staticObjects-holds all the static objects in the game 
std::map<sf::Color, MovingObjectFunc, CompareColor>- map to create a new moving object (read in Notes) in the game (factory map) 
by mapping color and function pointer (using MovingObjectFunc = std::function<std::unique_ptr<MovingObject>(float, float,  Level*)>)
and key sorting by functor
std::map<sf::Color, StaticObjectFunc, CompareColor>- same as MovingObject factory's map 

---- Algorithems ----
using stl algorithms 

----Design----
the game runs by the following rules:
main- call for GameController to run the game
 
class GameController - manage all the states in game the first state he show is MenuState that holds buttons with commands 
				     than he call for the update of the current state , and the render of the current state
		
class MenuState -holding Buttons  at any moment the user can :exit/start new game/enter the help page by pressing on of the buttons  that holding commandes
		     if he pressed new game he activated switch screen command and the game controller changed his state to InGameState wich is the game play screen 
		     than the game will run from level one.

class HelpScreenState- when player pressed controles/How To Play  the state is now help state wich showing to the user how to play or the controles of the game  

class InGameState- when player pressed new game the InGame State is activated than he proccess all the game play world
				 (updating UserIterFace, rendering,set the view, updaing objects positions by calling to player move function and level update) 

class Level - reading the objects from a tile map creating the objects by thair colors using the factories , updating the objects lists manage collisions in the game 

class UserInterface- as long as the game is running the InGameState updating the UI 

class GameOverState- when player finsh in success all the level or he died before the Game OverState is activate where the user can see the points he recives during the game
 
class GameObject- each object can set his position in the game and updating if he moving one , erasing option in certain situations  

from now we have the objects inheritate like we describes in the "Files" section each  moving object has his own move function,
the Pizza anemy and Player the move is depend of the curren state 
the pizza enemy and the player can insert new objects to the lists during the game (cheese weapon, salt bomb)
during the game gravity is applied to all moving objects in the game

for another information  UML  is added to the project


---- Bugs ----

---- Notes ----
1 . most of the moving objects creating by MovingObjectFactory, Additionally every moving objects holding his animation vector
2 . the static objects creating by StaticObjectFactory
in order to add levels do as the following instructions in "resourses" file:
1. add your level file name into - "Playlist.txt" (in a new line!!).
2. then in "CmakeList.txt" (still in resources file) and add the name of your level to the configure_file.


if you want to add new level , design your own level using the paint apllication to create a tile map and paint the map pixels with colores
you can copy a existing level and design hin by the current colores in the copied level 
the level format is "LevelX.png" (while X is the level number - must be in order and not just a random level number!!)
for example: if you level called  "Level4.txt"
add it in new line at the end of Playlist.txt
and than in "CmakeList.txt" add this: (in a new line)
configure_file ("Level4.txt" ${CMAKE_BINARY_DIR} COPYONLY)

for enjoy the game make sure you dont make heavy level (level heavily loaded with objects) 