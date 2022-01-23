# The-Catcher

**Overview:** 
  The Catcher is a simple console based gaming application created in C++. The idea of making a
game originated from a simple meme of a code that created a flying Helicopter as its output. That
meme gave us the idea of making a simple animation that quickly got converted into an idea for
a game that contained both animation and different conditions.

Initially, OpenGL was chosen as the graphic library but the project quickly shifted towards
SFML due to the difficulty to learn OpenGL and the limited time we had. So SFML is the main
input/output and drawing library for this project.

**Working:** 
  The Catcher is a simple game in which some items having different score points are dropped
from the screen height limit and you have to catch them using a board lying at the bottom thus
the name The Catcher. A successful catch results in the increase in score and a drop results in a
decrease in drop chances.

For now, the drop chances are fixed i.e 5, but in future releases difficulty selection may get
implemented that will allow you to have different drop chances for different difficulty.
3If you lose all the drop chances, you will be prompted with a screen saying gameover and you
will return to the main menu. All the score you earned will be stored in a file and can be accessed
later.

Talking about files, you can create a new accounts and access or delete existing accounts. All
your game data will be saved in files related to your accounts and will be appended with time.

**Code Access:**
The source code for this project is free and opensource licensed under the **Apache Licence 2.0**.
Any one who is interested can acces the code to play the game or study, test or modify the code
according to his/her needs.
