//Define a constant for our yellow led
const int YELLOW_LED = 13;
const int PIN_6 = 6;

//Function prototype. Allows us to call a function before the definition (at the end of the file)
void setup_serial();
/**
 * The setup function for today's lesson will be used
 * as our whole program. It will not repeat, or loop at the end. In this
 * way we can can create a non-repeating sequence of instructions *or* we can
 * tell it to repeat ourselves. 
 * 
 * We will not use "loop" function except to do-nothing after our program finishes.
 */
void setup() {
  //Enables us to call Serial.println() to display output.
  //Make sure to run Tools/Serial Monitor to see that output.
  setup_serial();
  //LED can go on and off, we can read pin #6 for HIGH or LOW voltage
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(PIN_6, INPUT);
  //Lets say "Hello World" in the longstanding tradition of Software Engineers
  Serial.println("Hello World");
  //Did you notice the output in your console? Now you can see into your program
  //with these print statements
  
  //Notice that the rest of the code is commented out
  //for each section of today's lession, you can uncomment
  //it at your own pace, and see what it does. Then explore
  //a bit to learn. When you are ready continue to the next
  //section

  /** Section 1: Operators, variables, math **/
  //First lets create an integer, assign it 0, and
  //then add some numbers into it. Lastly, we will print
  //it out, and see what we get out.
  /*int adder = 0;
  adder = 1 + 2;
  Serial.print("Our adder:");
  Serial.println(adder);*/
  //Knowing that you can use: + - * / can you multiply the
  //first 5 integer together?
  /*int multi = ...
  ...
  Serial.print("1 * 2 * ... * 5 is: ");
  Serial.println(multi);*/
  //Did you get: 120? If not keep trying!

  //There are many more operators: % << >> & | ^ ++ --
  //Can you figure out what several of these do?
  //Hint: experiment and explore.  If you get an error,
  // try to fix it.  You mentors will help.

  /** Section 2: conditionals **/

  //Often we want to print something but only if the program
  //has entered a certain state (an error has happened), the user won the game
  //or any other reason.
  //This is a conditional, that is do something only when a certain condition is met
  //For this we can use an if statement.  Think of it as an "if some condition is true, do X"

  //If 3 is greater than 2, print 3 is greater than 2
  /*if (3 > 2) {
    Serial.println("Three > Two, take that Two");   
  }
  //If 3 < 2 then panic
  if (3 < 2) {
    Serial.println("Something is very wrong here.");
  }*/
  //These statements are not very useful because the condition doesn't change,
  //however; if we add in memory (variables) then the condition can change and
  //we can react to events.
  /*int addition = 3 + 4;
  if (addition >= 10) {
    Serial.println("I added numbers above 10");
  }*/
  //Notice here we can read an external state to the program (pin voltage)
  //and respond to it. Frijoles padres! (Cool beans)
  //If the pin #6 is connected to high voltage
  //then turn on the led
  /*int pinState = digitalRead(PIN_6);
  if (pinState == HIGH) {
    digitalWrite(YELLOW_LED, HIGH);
  }*/
  //Can you figure out how to turn off the YELLOW_LED if PIN_6 is LOW?
  //Hint 1: what does if (...) {} else if (...) {} do?
  //Hint 2: what happens if this code lives in the loop function instead?
  //Hint 3: you'll need to supply PWR or GND voltage to pin D6 using a wire

  //Did you get the LED to turn on and off? Can you get it to turn on and off without
  //rerunning your program?

  //Here are some other things that help with conditionals: > < >= <= != == && ||
  //See if you can figure out what some of these do

  //**** Exploration Time! ****/
  //Can you detect 2 voltages?
  //Can you add 2 voltages?
}
/**
 * Loop function not used. We will write our own.
 */
void loop() {}
/**
 * **** You can safely ignore this until 2017-10-06 ****
 * A function that sets up the 1 USB serial cord supplied
 * by our Arduino.
 * 
 * Functions are reusable units of code that can be called multiple times,
 * or in this case it is used to separate out code (so you can ignore it).
 */
void setup_serial() {
  //In order for our Arduino board to produce text we can see in our screen,
  //it must send the text to display over the USB cord. This code sets up this
  //communication so we can display text output.
  //Serial is not ready, so we should tell it we wish to communicate at 9600 bits/S
  Serial.begin(9600);
  //Serial is turning on, so we will busy-wait until it is ready to communicate
  //so we don't lose messages while it turns on.
  while(!Serial) {}
  return;
}
