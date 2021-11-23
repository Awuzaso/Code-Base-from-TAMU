int M = 3;
int N = 3;


void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  
}

//X Pattern 
int x_pattern[3][3] = {  
   {1, 0, 1} ,   /*  initializers for row indexed by 0 */
   {0, 1, 0} ,   /*  initializers for row indexed by 1 */
   {1, 0, 1}   /*  initializers for row indexed by 2 */
};

//T Pattern
int t_pattern[3][3] = {  
   {1, 1, 1} ,   /*  initializers for row indexed by 0 */
   {0, 1, 0} ,   /*  initializers for row indexed by 1 */
   {0, 1, 0}   /*  initializers for row indexed by 2 */
};


void loop() {
  
  
  drawPattern(x_pattern); //
  delay(500);
  drawPattern(t_pattern); //
   delay(500);
  drawPattern(x_pattern); //
   delay(500);
}



void drawX(){
  
   digitalWrite(1,x_pattern[0][0]);
   digitalWrite(2,x_pattern[0][1]);
   digitalWrite(3,x_pattern[0][2]);
  
   digitalWrite(4,x_pattern[1][0]);
   digitalWrite(5,x_pattern[1][1]);
   digitalWrite(6,x_pattern[1][2]);
  
   digitalWrite(7,x_pattern[2][0]);
   digitalWrite(8,x_pattern[2][1]);
   digitalWrite(9,x_pattern[2][2]);
    
}

void drawPattern(int arr[3][3])
{

  int i, j, pinNumber;
 
  /* These are the variables we will use to keep track of the changes we need to consider as we iterate through each element of our 2D array. */
 
  for (i = 0; i < 3; i++){ 
    /* i keeps track of the row in the array */

    for (j = 0; j < 3; j++){
      /* j keeps track of the row in the array */
     
      pinNumber = ((i*3)+j)+1;
      Serial.print(pinNumber);

      /* We are using a mathematical formula to calculate the exact pin we want to select dependent upon the specific row (i) multiplied by 3 plus column (j) to get a value we can test for in a switch statement.*/
      
      /* Here we will call the digitalWrite function and in place of "LOW" or "HIGH", we will use the array value specified by i and j in our 2D array. Which pinout we will 
use is dependent upon the specific i and j */

           digitalWrite(pinNumber,arr[i][j]);
 
    } 
  }
  
}
  
  
  
  
  
  
