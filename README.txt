====== EX1 - SHAPES CALCULATOR =====
name: Re'em Hoisman
id: 2111694146

---- Program info ----
this program presenting a shape calculator by the following rules:
* the user enters one of the following "options" -
1. "cre" - the user creates one of the shapes: Triangle/Square/Rectangle (first char presents its shape)
		   than enters the edge size (if rectangle also the height size)
2. "en" - the user wants to enlarge a shape, enters also the number of shape and factor (the edges will be enlarge by this factor)
3  "red" - the user wants to reduce a shape, enters also the number of shape and factor (the edges will be reduce by this factor)
4. "draw" - after enters "draw" the user enters the index of the shape in the list the he wants to draw
5. "dup" - the user enters shape number and the amount of appearances of that shape.
		   it'll create new shape that will be inserted into the shape list
6. "stack" - after the user enters two shapes numbers it create new shape with the first shape is on top and the second shape is down
7. "del" - the user enters the number of shape from the list the he wants to delete
8. "help" - display the "help" information of the program
9. "exit" - prints "Goodbye" and exit the program.

---- Files ----
Calculator.h - contains the declaretions of class Calculator and its functions, members
Calculator.cpp - the implement of class Calculator functions.

Shape.h - contains the declaretions of class Shape and its functions, members
Shape.cpp - the implement of class Shape functions and constructor
			this class is the base class of all the shapes in the program

Square.h - contains the declaretions of class Square and its functions
Square.cpp - the implement of class Square functions. derived class of class Shape (inhertance it's public functions and constructor)

Triangle.h - contains the declaretions of class Triangle and its functions
Triangle.cpp - the implement of class Triangle functions. derived class of class Shape (inhertance it's public functions and constructor)

Rectangle.h - contains the declartion of class Rectangle and its functions, member (m_height)
Rectangle.cpp - the implement of class Rectangle functions. derived class of class Shape (inhertance it's public functions)

StackShape.h - contains the declartion of class StackShape and its functions
StackShape.cpp - the implement of class StackShape functions. derived class of class Shape (inhertance it's public functions)
				 most of the functions in shape is being overrided

dupShape.h - contains the declartion of class StackShape and its functions
dupShape.cpp - the implement of class StackShape functions. derived class of class Shape (inhertance it's public functions)
				 most of the functions in shape is being overrided

---- Data base ----
enum Options - contains all of the options that the user can choose

unordered_map <string, Options> - get strign from the user and translate it to one of the calculator options

vector <shared_ptr<Shape>> m_shapes - (in class Calculator) being used by polimorphism 
									  (shape is the base class of all of the shapes in the program all stores in that vector)
vector <shared_ptr<Shape>> m_shapes - (in class StackShape) holds the two shapes (that first one is on top the second one is down)
		 
---- Algorithems ----


----Design----
the game runs by the following rules:
Class Calculator - manage all the shapes calculator proccess. contains all the shapes in vector of shared_ptr
				   after the user choose one of the calculator options, it has control on which shape needs to be manipulated 

class Shape - base class of all shapes in that program. holds as members the type and the edge size of the shape.
			  have implemetion (getters and resize the edge size). also have and pure virtual function "draw"

class Square - besides draw, all of this class function is being implement in class Shape (its base class, include constructor)

class Triangle - besides draw, all of this class function is being implement in class Shape (its base class, include constructor)

class Rectangle - differently from classes Square and Triangle this class has another member of height therfore this class is using 
				  some functions from Shape but also overrides some of its function (because of the different implementation)

class StackShape - this class presents a shape the is being built from two existing shapes, therfore vector of shared_ptr holds those shapes
				   do itll be able to use those shapes functunality. this class also overrides some of Shape class functions
				   
class dupShape - this class holding a shape that is actually existing shape times 'm_amount'. so it use those shapes functions and overrides 
			     class Shape functions

---- Bugs ----

---- Notes ----
