
// This program sets five digital outputs to high

int fetPin1 = 3; //Thumb heating element
int fetPin2 = 5; //Index and Middle Finger heating element
int fetPin3 = 6; //Ring and pinky finger heating element
int fetPin4 = 9; //Palm heating element
int fetPin5 = 10; //Rear of hand heating element



void setup() {                
  // initialize the digital pins as an output.
  pinMode(fetPin1, OUTPUT);
  pinMode(fetPin2, OUTPUT);  
  pinMode(fetPin3, OUTPUT);
  pinMode(fetPin4, OUTPUT);
  pinMode(fetPin5, OUTPUT);
}

void loop() {
  //Turn on all heating elements continuously
  digitalWrite(fetPin1, HIGH); 
  digitalWrite(fetPin2, HIGH); 
  digitalWrite(fetPin3, HIGH); 
  digitalWrite(fetPin4, HIGH); 
  digitalWrite(fetPin5, HIGH); 
}

