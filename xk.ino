


String s;

int mode;


void setup () {
  pinMode (pin_speaker, OUTPUT);
  pinMode (pin_led, OUTPUT);

  pinMode (pin_wheel_1, OUTPUT);
  pinMode (pin_wheel_2, OUTPUT);
  pinMode (pin_wheel_3, OUTPUT);
  pinMode (pin_wheel_4, OUTPUT);

  pinMode (pin_s1, INPUT);
  pinMode (pin_s2, INPUT);

  pinMode (pin_hall, INPUT);
  
  #ifdef DEBUG
  Serial.begin (115200);
  Serial.println ("yikes! bikes! - debug mode");
  #endif
  
  
  mode = 0;
  
  
  vs.init (pin_speaker);
  vss.init ();
  vss.start ();
  
  
  if (digitalRead (pin_s1)==HIGH) {
    if (digitalRead (pin_s2)==HIGH) {
      #ifdef DEBUG
      Serial.println ("TEST MODE!");
      #endif
      //test mode
      mode = 3;
    } else {
      #ifdef DEBUG
      Serial.println ("PERFORMANCE MODE (2)!");
      #endif
      
      //performance mode
      initPerformanceMode ();
      mode = 2;
    }
  } else {
    #ifdef DEBUG
    Serial.println ("LOOPS MODE (1)!");
    #endif
    
    // loops mode
    mode = 1;
  }
  
  // DEBUG reasons!
  //mode = 2;
  //initPerformanceMode ();
  
  
  
}

void loop () {
  switch (mode) {
    case 0:
      break;
    case 1:
      loopsMode ();
      break;
    case 2:
      performanceMode ();
      break;
    case 3:
      testMode ();
      break;
  }

}

void testMode () {
  int tv;
  boolean snd = false;
  Reedster tach;
  
  tv = 31;
  
  digitalWrite (pin_led, HIGH);
  digitalWrite (pin_wheel_1, HIGH);
  digitalWrite (pin_wheel_2, HIGH);
  digitalWrite (pin_wheel_3, HIGH);
  digitalWrite (pin_wheel_4, HIGH);
  
  tach.init (A1);
  
  
  
  while (true) {
    snd = false;
    if (digitalRead (pin_s2)==HIGH) {
      tone (pin_speaker, 110);
      snd = true;
    }
    if (digitalRead (pin_s1)==HIGH) {
      tone (pin_speaker, 440);
      snd = true;
    }
    
    if (!snd) noTone (pin_speaker);
  /*  
    if (tach.step ()) {
      Serial.println ("Tach!");
    }
    */
  }
}
