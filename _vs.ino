class Reedster {
public:
  void init (int _pin) {
    pin_led = 7;
    
    pin = _pin;
    
    revs = 0;
    counter = 0;
    
    time_lapse = 1000;
    time_debounce = 20;
    
    
    
    input_ready = true;
    Serial.begin (115200);
    
    time_keep = millis ();
    digitalWrite (pin_led, LOW);
  }
  
  
  
  boolean step () {
    r = false;
    if (input_ready) {
      v = digitalRead (pin);
      
      if (v==HIGH) {
        digitalWrite (pin_led, HIGH);
        debounce = millis ();
        input_ready = false;
        r = true;
        counter++;
      }
    } else {
      if (millis ()-debounce>=time_debounce) {
        digitalWrite (pin_led, LOW);
        input_ready = true;
      }
    }
    
    if (millis ()-last_time>=time_lapse) {
      revs = counter / time_lapse;
      revs = counter;
      last_time = millis ();
      counter = 0;
    }
    
    return r;
  }
  
  int rpt () {
    return revs;
  }

private:
    
  int i;
  int v;
  boolean r;
  
  int pin;
  int counter;
  int revs;
  
  long debounce;
  
  long time_keep;
  long last_time;
  long time_lapse;
  long time_debounce;
  
  boolean input_ready;
  
  
  int pin_led;
};


class VortexSynth {
public:
  void init (int _pin) {
    pin = _pin;
    
    low_noise = false;
    high_noise = false;
  }
  
  
  void play (String ucml_msg) {
    // Universal Coded Music Language
    //Serial.println (ucml_msg);
    
    
    
    if (ucml_msg.equals ("")) {
      
    } else if (ucml_msg.equals (".")) {
      high_noise = false;
      low_noise = false;
      
      noTone (pin);
    } else if (ucml_msg.equals ("s") || ucml_msg.equals ("sL")) {
      high_noise = true;
      low_noise = false;
    } else if (ucml_msg.equals ("S") || ucml_msg.equals ("SL")) {
      high_noise = false;
      low_noise = true;
    } else {
      high_noise = false;
      low_noise = false;
            
      last_freq = noteFreq (ucml_msg);
      tone (pin, last_freq);
      //Serial.println (last_freq);
    } 
    
    //Serial.println (ucml_msg);
  }
  
  int noteFreq (String note) {
    int f = -1;

    for (int i=0; i<89; i++) {
      if (note.equals (note_names [i])) f = note_values [i];
    }


    return f;
  }
  
  void step () {
    if (low_noise) {
      tone (pin, (int)random (31, 4978));
    }
    if (high_noise) {
      tone (pin, (int)random (4979, 8024));
    }
  }
  
  int pin;
  
  int freq;
  int last_freq;
  
  boolean low_noise;
  boolean high_noise;
};
