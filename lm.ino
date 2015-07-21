Reedster tach;

void loopsMode () {
  int seq;
  
  Serial.println ("loops mode!");
  
  // setup
  tach.init (pin_hall);
  
  boolean ok = false;
  
  digitalWrite (pin_led, HIGH);
  while (digitalRead (pin_s1)!=HIGH);
  digitalWrite (pin_led, LOW);
  
  randomSeed (millis ());
  
  initSeqBleep ();
  
  while (true) {
    seqBleep ();
     
    if (digitalRead (pin_s1)) {
      initSeqBleep ();
    }
  }

}

// Bleep specific
const int bleep_max = 192;
const int bleep_min = 12;
const int bleep_avg = (bleep_max+bleep_min)/2;


int bleep_freq_min;
int bleep_freq_max;

int bleep_frequency;


// General LM
int lm_min_range;
int lm_max_range;
int lm_speed;
int lm_max_speed;

int lm_value;

int count = 0;
int count2;

int lm_counter = 0;

/// BLEEP
void initSeqBleep () {
  lm_value = lm_min_range = bleep_min;
  lm_max_range = bleep_max;
  
  lm_speed = 1;
  lm_max_speed = 17;
  
  randomSeed (millis ());
  
  bleep_frequency = 440;
  if (random (100)>80) bleep_frequency = random (110, 666);

  
  int ptn = random (0, 5);
  switch (ptn) {
    case 0:
      vss.ptn_inv01 ();
      break;
    case 1:
      vss.ptn_inv02 ();
      break;
    case 2:
      vss.ptn_inv03 ();
      break;
    case 3:
      vss.ptn_inv04 ();
      break;
    case 4:
      vss.ptn_inv05 ();
      break;
  }
 
}

void seqBleep () {
  // Organic glow
  //tone (pin_speaker, 60); 
  if (++lm_counter>=500) {
    if (lm_speed>0) {
      if (lm_value<lm_max_range) lm_value+= lm_speed;
      else {
        lm_speed = -(random (1, lm_max_speed));
        
        lm_max_range = random (bleep_avg, bleep_max);
        lm_min_range = random (bleep_min, bleep_avg);
      }
    } else
    if (lm_speed<0) {
      if (lm_value>lm_min_range) lm_value+= lm_speed;
      else {
        lm_speed = random (1, lm_max_speed);
        
        lm_max_range = random (bleep_avg, bleep_max);
        lm_min_range = random (bleep_min, bleep_avg);
      }
    }
    lm_counter = 0;
  }
  
  String s = vss.step ();
  if (s!="") {
    vs.play (s);
    Serial.println (s);
  }
  
  vs.step ();
  
  boolean t = tach.step ();

  if (t) {
    analogWrite (5, 255);
    analogWrite (6, 255);
    analogWrite (9, 255);
    analogWrite (10, 255);
    
    analogWrite (7, 255);
    tone (pin_speaker, 1175);
    delay (10);

  } else {
    analogWrite (5, lm_value);
    analogWrite (6, lm_value);
    analogWrite (9, lm_value);
    analogWrite (10, lm_value);
    
    analogWrite (7, lm_value);
  }
  

}


