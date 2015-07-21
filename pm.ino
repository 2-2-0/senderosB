int pm_min_range;
int pm_max_range;

int pm_value;

int pm_speed;

int p_mode;

long pm_last_time;
int pm_count;
//int pm_mode;

int pm_f_value;

void initPerformanceMode () {
  

//  delay (1000);
  
  for (int i=0; i<15; i++) {
    digitalWrite (pin_led, HIGH);
    delay (120);
    digitalWrite (pin_led, LOW);
    delay (80);
  }
//  delay (3000);
  
  vss.init ();
  
  /// INIT performance mode
  
  vss.ptn_01 ();
  
  
  pm_min_range = 24;
  pm_max_range = 255;
  pm_value = pm_min_range;
  
  pm_speed = 1;
  
  pm_count = 0;
  
  pm_last_time = millis ();
  
  randomSeed (millis ());
  p_mode = random (3);
  
  //p_mode = 2;
  
  //vss.listSeqSteps ();
  vss.start ();
  
  syncMode ();
}
void pickPattern (int p) {
  switch (p) {
    case 0:
      vss.ptn_01 ();
      break;
    case 1:
      vss.ptn_02 ();
      break;
    case 2:
      vss.ptn_03 ();
      break;
    case 3:
      vss.ptn_04 ();
      break;
    case 4:
      vss.ptn_05 ();
      break;
    case 5:
      vss.ptn_06 ();
      break;
    case 6:
      vss.ptn_07 ();
      break;
    case 7:
      vss.ptn_08 ();
      break;
    case 8:
      vss.ptn_09 ();
      break;
    case 9:
      vss.ptn_10 ();
      break;
    case 10:
      vss.ptn_11 ();
      break;
    case 11:
      vss.ptn_12 ();
      break;
    case 12:
      vss.ptn_13 ();
      break;
    case 13:
      vss.ptn_14 ();
      break;
    case 14:
      vss.ptn_15 ();
      break;
    case 15:
      vss.ptn_16 ();
      break;
    case 16:
      vss.ptn_17 ();
      break;
    case 17:
      vss.ptn_18 ();
      break;
    case 18:
      vss.ptn_19 ();
      break;
  }
}
int pattern = 0;
int p_count = 0;

void syncMode () {
  String s;
  int count = 0;
  
  vss.ptn_01 ();
  
  boolean ok = false;
  while (!ok) {
    if (digitalRead (pin_s1)) {
      vss.resync (pin_s1);
      count = 0;
    }
    
    s = vss.step ();
    vs.play (s);
    
    
    
    if (s.indexOf ("C")!=-1) {
      Serial.println ("Sync!");
      
      /////////////////////////////////
      //****************************** COUNT
      if (count<8) count++;
      else ok = true;
    }
    
  }

  digitalWrite (pin_led, HIGH);

  vss.ptn_calib ();
  
  noTone (pin_speaker);
  
  boolean moment = false;
  
  ok = false;
  while (!ok) {
    if (digitalRead (pin_s1)) moment = true;
    s = vss.step ();
    if (vss.pattern_end && moment) ok = true;
  }
  
  digitalWrite (pin_led, LOW);
  
  pattern = 1;
  pickPattern (pattern);
}


void performanceMode () {
  boolean pe;
  String s;

  
  randomSeed (millis ());

  

  if (++pm_count>200) {
    switch (p_mode) {
      case 0:
        pm_value = random (64, 255);
        //Serial.println (pm_f_value);
        break;
      case 1:
        // constant glow
        pm_value+= pm_speed;
        if (pm_speed>0) {
          if (pm_value>=pm_max_range) {
            pm_speed = -1;
          }
        } else
        if (pm_speed<0) {
          if (pm_value<=pm_min_range) {
            pm_speed = 1;
          }
        }
        
        //pm_last_time = millis ();          
        //Serial.println (pm_value);
        break;
      case 2:
        // organic glow
        pm_value+= pm_speed;
        if (pm_speed>0) {
          if (pm_value>=pm_max_range) {
            pm_max_range = (int)random (191, 255);
            pm_speed = -(int)random (1, 15);
          }
        } else
        if (pm_speed<0) {
          if (pm_value<=pm_min_range) {
            pm_min_range = (int)random (0, 64);
            pm_speed = (int)random (1, 15);
          }
        }
        break;
    }  
    //Serial.println (pm_value);
    pm_count = 0;
  }
  

  s = vss.step ();
  if (s!="") {
    
    if (s!=".") {
      pm_f_value = 0;
    } else {
      pm_f_value = pm_value;
////////// HERE
    }
    
    if (vss.pattern_end) {
        if (p_count<3) {
          p_count++;
          Serial.print ("p_count: ");
          Serial.println (p_count);
        } else {
          p_count = 0;
          if (pattern<19) {
            pattern++;
            Serial.print ("ptn: ");
            Serial.println (pattern);
            pickPattern (pattern);
          } else {
            // glow seq hang out
            Serial.println ("Game OVAH!");
            while (true);
          }
        }
      }
    
    //Serial.println (s);
    vs.play (s);
  }
  vs.step ();

  analogWrite (pin_wheel_1, pm_f_value);
  analogWrite (pin_wheel_2, pm_f_value);
  analogWrite (pin_wheel_3, pm_f_value);
  analogWrite (pin_wheel_4, pm_f_value);
  analogWrite (pin_led, pm_f_value);
}
