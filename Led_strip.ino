/*
 * Gkoutzas Nikos
 * Led strip (30 leds) - 5 Volt
 * July 2021
 * Arduino - 9 animations , color and brightness control (of each animation) at any time via keypad (4x3) 
 * [With button '0' ,you can turn off the led strip]
 * The code is big enough ,because you can change/interrupt any animation you want at any time ,while another animation is running that period.
 * (You should not have to wait, until an animation stops).
  
 * Have fun ! 
 */



#include <FastLED.h>
#include <Keypad.h>

#define LED_STRIP_PIN 13
#define NUM_OF_LEDS 30

CRGB leds[NUM_OF_LEDS];
int brightness = 255;

uint8_t hue__rgb_wave = 0;
uint8_t hue_sea_waves = 0;

int zero_ = 0;
int *pick_color_variable = &zero_;

int fade_variable = 0;
int fade_variable_with_colors = 0;
int fill_and_clear_var = 0;
int speed_of_rgb_wave = 9;

bool direction_of_rgb_wave = true;
bool fill_and_clear__start = true;
bool interruption_circle_rgb , interruption_rainbow_rgb , interruption_hit_and_escape;

bool _0__pressed = false;
bool _1__pressed = false;
bool _2__pressed = false;
bool _3__pressed = false;
bool _4__pressed = false;
bool _5__pressed = false;
bool _6__pressed = false;
bool _7__pressed = false;
bool _8__pressed = false;
bool _9__pressed = false;

int var_fill_and_clear__pos = NUM_OF_LEDS;
int var_fill_and_clear__pos__2 = 0;

bool fill_and_clear__UP = true;
int fade_brightness = 0;
bool fade_UP = true;
bool fade_enable__ = false;
bool fade_with_colors_;

const byte ROWS = 4; 
const byte COLS = 3; 

char keys[ROWS][COLS] = { 
                          {'1','2','3'},
                          {'4','5','6'},
                          {'7','8','9'},
                          {'*','0','#'}
                        };

byte rowPins[ROWS] = {8, 7, 6, 5}; 
byte colPins[COLS] = {4, 3, 2}; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



// Number of colors: 18
CRGB array_colors[] = {CRGB::Red , CRGB::Green , CRGB::Blue , CRGB::Yellow , CRGB::GreenYellow , CRGB::DeepSkyBlue , CRGB::Olive , CRGB::Navy , CRGB::Magenta , CRGB::Orange , 
                       CRGB::DeepPink , CRGB::Chocolate , CRGB::Coral , CRGB::Indigo , CRGB::Cyan , CRGB::Purple , CRGB::White , CRGB::Black
                      };



void setup()
{
  FastLED.addLeds<WS2812B, LED_STRIP_PIN, GRB>(leds, NUM_OF_LEDS);
  pick_color(array_colors[17] , 0);
  Serial.begin(9600);
  //passcode(); // Just in case you want to type a passcode so that you "enable" led strip and start the animations
}



void pick_color(CRGB color , int brightness)
{
  for(int i = 0; i < NUM_OF_LEDS; i++)
  {
    leds[i] = array_colors[*pick_color_variable];
    FastLED.setBrightness(brightness);
    FastLED.show();
  }
}


void fade_in_fade_out(CRGB color , char key , int __COLORS__ , bool fade_with_colors_)
{
  int var;

  while(true)
  {
    for(int col = 0; col <= __COLORS__; col++)
    {
      if(fade_UP)  // fade in
      {
        if(fade_enable__)  // if true ,then (in case I have changed color) the brightness continues from the last value brightness
        {
          var = fade_brightness;
        }
        else  // otherwise , brightness starts from the beginning
        {
          var = 0;
        }
        for(int k = var; k < 255; k += 3)
        {
          for(int i = 0; i < NUM_OF_LEDS; i++)
          {
            key = keypad.getKey();

            if(key == '0')
            {
              _0__pressed =  true;   // number '0' just pressed
              return;
            }
            
            if(key == '1')
            {
              --*pick_color_variable;
              _1__pressed =  true;   // number '1' just pressed
              return;
            }
            
            else if(key == '2')
            {
              _2__pressed = true; // number '2' just pressed
  
              if(fade_variable < 16)
              {
                fade_variable++;
              }
              else
              {
                fade_variable = 0;
              }
              fade_UP = true;
              fade_brightness = k;
              fade_enable__ = true;
              return; 
            }

            else if( !fade_with_colors_ && key == '3')
            {
              fade_variable -= 1;
              _3__pressed = true; // number '3' just pressed
              return; // exit from inner for-loop
            }

            else if(key == '4')
            {
              _4__pressed = true; // number '4' just pressed
              return;
            }

            else if(key == '5') // and so on...
            {
              _5__pressed = true;
              return;
            }

            else if(key == '6')
            {
              _6__pressed = true;
              return;
            }

            else if(key == '7')
            {
              _7__pressed = true;
              return;
            }

            else if(key == '8')
            {
              _8__pressed = true;
              return;
            }

            else if(key == '9')
            {
              _9__pressed = true;
              return;
            }
            
            else if(fade_with_colors_)  // number '3' function...(auto change colors)
            {
              color = array_colors[fade_variable_with_colors];
            }
            
            fade_enable__ = false;
            fade_UP = false; // This gets false , so that leds fade out
  
            FastLED.setBrightness(k);
            leds[i] = color;
            FastLED.show();
          }
        }
      }
      
      
      else
      {
        if(fade_enable__)  // if true ,then (in case I have changed color) the brightness continues from the last value brightness
        {
          var = fade_brightness;
        }
        else
        {
          var = 255;  // otherwise , brightness starts from the beginning (which is 255, cause we are in 'fade out')
        }
        for(int k = var; k >= 0; k -= 3)
        {
          for(int i = 0; i < NUM_OF_LEDS; i++)
          {
            key = keypad.getKey();

            if(key == '0')
            {
              _0__pressed =  true;   // number '0' just pressed
              return;
            }
            
            if(key == '1')
            {
              --*pick_color_variable;
              _1__pressed =  true; // number '1' just pressed
              return;
            }
            else if(key == '2')
            {
              if(fade_variable < 16)
              {
                fade_variable++;
              }
              else
              {
                fade_variable = 0;
              }
              fade_UP = false;
              fade_brightness = k;
              fade_enable__ = true;
              _2__pressed = true;
              return;
            }
            
            else if( !fade_with_colors_ && key == '3')
            {
              fade_variable -= 1;
              _3__pressed = true; // number '3' just pressed
              return; 
            }


            else if(key == '4')
            {
              _4__pressed = true; // number '4' just pressed
              return;
            }

            else if(key == '5')
            {
              _5__pressed = true;
              return;
            }

            else if(key == '6')
            {
              _6__pressed = true;
              return;
            }

            else if(key == '7')
            {
              _7__pressed = true;
              return;
            }
            
            else if(key == '8')
            {
              _8__pressed = true;
              return;
            }

            else if(key == '9')
            {
              _9__pressed = true;
              return;
            }
            
            else if(fade_with_colors_)  // number '3' function...(auto change colors)
            {
              color = array_colors[fade_variable_with_colors];
            }
            
            fade_enable__ = false;
            fade_UP = true;  
            
  
            FastLED.setBrightness(k);
            leds[i] = color;
            FastLED.show();
          }
        }
        if(fade_with_colors_)
        {
          if(fade_variable_with_colors < 16)
          {
            fade_variable_with_colors++;
          }
          else
          {
            fade_variable_with_colors = 0;
          }
        }
      }
    }
  }
}





void fill_and_clear(CRGB color , char key)
{
  int mov = 0;
  int tail;
  if(fill_and_clear__start)
  {
    for(int i = 0; i < NUM_OF_LEDS; i++)
    {
      leds[i] = CRGB::Black;
      FastLED.show();
    }
    var_fill_and_clear__pos__2 = 0;
    tail = NUM_OF_LEDS;
  }
  else
  {
    tail = var_fill_and_clear__pos;
  }

  while(true)
  {
    if(fill_and_clear__UP)
    {
      for(int l = 1; l < NUM_OF_LEDS; l++)
      {
        for(int i = var_fill_and_clear__pos__2; i < tail; i++)
        {
          key = keypad.getKey();

          if(key == '0')
          {
            fill_and_clear__UP = true;
            fill_and_clear__start = true;
            _0__pressed =  true;   // number '0' just pressed
            return;
          }
            
          if(key == '1')
          {
            --*pick_color_variable;
            fill_and_clear__UP = true;
            fill_and_clear__start = true;
            _1__pressed = true;
            return;
          }
    
          else if(key == '2')
          {
            fill_and_clear__UP = true;
            fill_and_clear__start = true;
            _2__pressed = true;
            return;
          }
    
          else if(key == '3')
          {
            fill_and_clear__UP = true;
            fill_and_clear__start = true;
            _3__pressed = true;
            return;
          }
    
          else if(key == '4')
          {
            fill_and_clear__start = false;
            _4__pressed = true;
            if(fill_and_clear_var < 16)
            {
              fill_and_clear_var++;
            }
            else
            {
              fill_and_clear_var = 0;
            }
            var_fill_and_clear__pos = tail;
            var_fill_and_clear__pos__2 = i;
            for(int h = NUM_OF_LEDS; h >= tail; h--)
            {
              leds[h] = array_colors[fill_and_clear_var];
              FastLED.show();
            }
            for(int h = 0; h < tail; h++)
            {
              leds[h] = CRGB::Black;
              FastLED.show();
            }
            
            return;
          }

          else if(key == '5')
          {
            fill_and_clear__UP = true;
            fill_and_clear__start = true;
            _5__pressed = true;
            return;
          }

          else if(key == '6')
          {
            fill_and_clear__UP = true;
            fill_and_clear__start = true;
            _6__pressed = true;
            return;
          }

          else if(key == '7')
          {
            fill_and_clear__UP = true;
            fill_and_clear__start = true;
            _7__pressed = true;
            return;
          }

          else if(key == '8')
          {
            fill_and_clear__UP = true;
            fill_and_clear__start = true;
            _8__pressed = true;
            return;
          }

          else if(key == '9')
          {
            fill_and_clear__UP = true;
            fill_and_clear__start = true;
            _9__pressed = true;
            return;
          }
          
          var_fill_and_clear__pos__2 = 0;
          
          if(i == tail-1)
          {
            tail--;
          }
          control_brightness(key);
    
          FastLED.setBrightness(brightness);
          leds[i] = color;
          FastLED.show();
          delay(30);
          leds[i-1] = CRGB::Black;
        }
      }

      delay(60);
      var_fill_and_clear__pos__2 = 0;
      fill_and_clear__UP = false;
    } 


    if( ! fill_and_clear__UP)
    {
      for(int l = var_fill_and_clear__pos__2; l < NUM_OF_LEDS; l++)
      {
        //Serial.println(l);
        for(int i = var_fill_and_clear__pos__2; i >= 0; i--)
        {
          key = keypad.getKey();

          if(key == '0')
          {
            fill_and_clear__UP = true;
            fill_and_clear__start = true;
            _0__pressed =  true;   // number '0' just pressed
            return;
          }
            
          if(key == '1')
          {
            --*pick_color_variable;
            fill_and_clear__UP = true;
            fill_and_clear__start = true;
            _1__pressed = true;
            return;
          }
    
          else if(key == '2')
          {
            fill_and_clear__UP = true;
            fill_and_clear__start = true;
            _2__pressed = true;
            return;
          }
    
          else if(key == '3')
          {
            fill_and_clear__UP = true;
            fill_and_clear__start = true;
            _3__pressed = true;
            return;
          }
    
          else if(key == '4')
          {
            fill_and_clear__start = false;
            _4__pressed = true;
            if(fill_and_clear_var < 16)
            {
              fill_and_clear_var++;
            }
            else
            {
              fill_and_clear_var = 0;
            }
            
            var_fill_and_clear__pos = ++var_fill_and_clear__pos__2;
            for(int h = NUM_OF_LEDS; h >= var_fill_and_clear__pos; h--)
            {
              leds[h] = array_colors[fill_and_clear_var];
              FastLED.show();
            }
            for(int h = 0; h < var_fill_and_clear__pos; h++)
            {
              leds[h] = CRGB::Black;
              FastLED.show();
            }
            for(int m = i; m >= 0; m--)
            {
              leds[m-1] = array_colors[fill_and_clear_var];
              leds[m] = CRGB::Black;;
              FastLED.show();
              delay(30);
            }
            
            return;
          }

          else if(key == '5')
          {
            fill_and_clear__UP = true;
            fill_and_clear__start = true;
            _5__pressed = true;
            return;
          }

          else if(key == '6')
          {
            fill_and_clear__UP = true;
            fill_and_clear__start = true;
            _6__pressed = true;
            return;
          }

          else if(key == '7')
          {
            fill_and_clear__UP = true;
            fill_and_clear__start = true;
            _7__pressed = true;
            return;
          }

          else if(key == '8')
          {
            fill_and_clear__UP = true;
            fill_and_clear__start = true;
            _8__pressed = true;
            return;
          }

          else if(key == '9')
          {
            fill_and_clear__UP = true;
            fill_and_clear__start = true;
            _9__pressed = true;
            return;
          }
            
          control_brightness(key);
    
          FastLED.setBrightness(brightness);
          leds[i-1] = color;
          FastLED.show();
          delay(30);
          leds[i] = CRGB::Black;
        }
        var_fill_and_clear__pos__2++;
      }
    
      delay(60);
      var_fill_and_clear__pos__2 = 0;
      fill_and_clear__UP = true;
      tail = NUM_OF_LEDS;
      fill_and_clear__start = true;
    } 
  }
}




void interrupt_function_circle_rgb(char key)
{
    if(key == '0')
    {
      _0__pressed = true;
      interruption_circle_rgb = true;
    }
    else if(key == '1')
    {
      --*pick_color_variable;
      _1__pressed = true;
      interruption_circle_rgb = true;
    }
    else if(key == '2')
    {
      _2__pressed = true;
      interruption_circle_rgb = true;
    }
    else if(key == '3')
    {
      _3__pressed = true;
      interruption_circle_rgb = true;
    }
    else if(key == '4')
    {
      _4__pressed = true;
      interruption_circle_rgb = true;
    }
    else if(key == '6')
    {
      _6__pressed = true;
      interruption_circle_rgb = true;
    }
    else if(key == '7')
    {
     _7__pressed = true;
     interruption_circle_rgb = true;
    }
    else if(key == '8')
    {
      _8__pressed = true;
      interruption_circle_rgb = true;
      return;
    }
    else if(key == '9')
    {
      _9__pressed = true;
      interruption_circle_rgb = true;
      return;
    }
}




void circle_RGB(char key)
{   
  interruption_circle_rgb = false;
  FastLED.setBrightness(brightness);
  
  while(true)
  {
    int R = 255;
    int G , B = 0;
    
  
    for(G = 0; G < 255; G+=5)
    {
      for(int i = 0; i < NUM_OF_LEDS; i++)
      {
        
        key = keypad.getKey();
        interrupt_function_circle_rgb(key);
        if(interruption_circle_rgb)
        {
          return;
        }
        control_brightness(key);
        leds[i] = CRGB(R , G , B);
        FastLED.show();
      }
    }
    
    for(R = 255; R > 0; R-=5)
    {
      for(int i = 0; i < NUM_OF_LEDS; i++)
      {
        key = keypad.getKey();
        control_brightness(key);
        interrupt_function_circle_rgb(key);
        if(interruption_circle_rgb)
        {
          return;
        }
        leds[i] = CRGB(R , G , B);
        FastLED.show();
      }
    }
    
    for(B = 0; B < 255; B+=5)
    {
      for(int i = 0; i < NUM_OF_LEDS; i++)
      {
        key = keypad.getKey();
        control_brightness(key);
        interrupt_function_circle_rgb(key);
        if(interruption_circle_rgb)
        {
          return;
        }
        leds[i] = CRGB(R , G , B);
        FastLED.show();
      }
    }
  
    for(G = 255; G > 0; G-=5)
    {
      for(int i = 0; i < NUM_OF_LEDS; i++)
      {
        key = keypad.getKey();
        control_brightness(key);
        interrupt_function_circle_rgb(key);
        if(interruption_circle_rgb)
        {
          return;
        }
        leds[i] = CRGB(R , G , B);
        FastLED.show();
      }
    }
  
    for(R = 0; R < 255; R+=5)
    {
      for(int i = 0; i < NUM_OF_LEDS; i++)
      {
        key = keypad.getKey();
        control_brightness(key);
        interrupt_function_circle_rgb(key);
        if(interruption_circle_rgb)
        {
          return;
        }
        leds[i] = CRGB(R , G , B);
        FastLED.show();
      }
    }
  
    for(B = 255; B > 0; B-=5)
    {
      for(int i = 0; i < NUM_OF_LEDS; i++)
      {
        key = keypad.getKey();
        control_brightness(key);
        interrupt_function_circle_rgb(key);
        if(interruption_circle_rgb)
        {
          return;
        }
        leds[i] = CRGB(R , G , B);
        FastLED.show();
      }
    }
  }
}



void interrupt_function_rainbow(char key)
{
    if(key == '0')
    {
      _0__pressed = true;
      interruption_rainbow_rgb = true;
    }
    else if(key == '1')
    {
      --*pick_color_variable;
      _1__pressed = true;
      interruption_rainbow_rgb = true;
    }
    else if(key == '2')
    {
      _2__pressed = true;
      interruption_rainbow_rgb = true;
    }
    else if(key == '3')
    {
      _3__pressed = true;
      interruption_rainbow_rgb = true;
    }
    else if(key == '4')
    {
      _4__pressed = true;
      interruption_rainbow_rgb = true;
    }
    else if(key == '5')
    {
      _5__pressed = true;
      interruption_rainbow_rgb = true;
      return;
    }
    else if(key == '7')
    {
     _7__pressed = true;
     interruption_rainbow_rgb = true;
    }
    else if(key == '8')
    {
      _8__pressed = true;
      interruption_rainbow_rgb = true;
      return;
    }
    else if(key == '9')
    {
      _9__pressed = true;
      interruption_rainbow_rgb = true;
      return;
    }
}



void RGB_wave(char key)
{
  interruption_rainbow_rgb = false;
  FastLED.setBrightness(brightness);
  
  unsigned long prev_timer = 0;

  while(true)
  {
    unsigned long cur_timer = millis();
    key = keypad.getKey();
    
    interrupt_function_rainbow(key);
    if(interruption_rainbow_rgb)
    {
     return;
    }
     
    control_brightness(key);
    for (int i = 0; i < NUM_OF_LEDS; i++) 
    {
      leds[i] = CHSV(hue__rgb_wave + (i * 10) , 255 , 255);
    }
    
    if(cur_timer - prev_timer >= speed_of_rgb_wave)
    {
      hue__rgb_wave++;   
      prev_timer = cur_timer;
    }
    
    //Serial.println(speed_of_rgb_wave);
    
    if(key == '6')
    {
      GOTO_IF:if(direction_of_rgb_wave)
      {
        if(speed_of_rgb_wave == 1)
        {
          direction_of_rgb_wave = false;
        }
        else if(speed_of_rgb_wave > 1)
        {
          speed_of_rgb_wave -= 4;
        }
      }
      if( ! direction_of_rgb_wave)
      {
        if(speed_of_rgb_wave == 9)
        {
          direction_of_rgb_wave = true;
          goto GOTO_IF;
        }
        else if(speed_of_rgb_wave < 9)
        {
          speed_of_rgb_wave += 4;
        }
      }
    }
    FastLED.show();
  }
}


void interrupt_function_hit_and_escape(char key)
{
    if(key == '0')
    {
      _0__pressed = true;
      interruption_hit_and_escape = true;
    }
    else if(key == '1')
    {
      --*pick_color_variable;
      _1__pressed = true;
      interruption_hit_and_escape = true;
    }
    else if(key == '2')
    {
      _2__pressed = true;
      interruption_hit_and_escape = true;
    }
    else if(key == '3')
    {
      _3__pressed = true;
      interruption_hit_and_escape = true;
    }
    else if(key == '4')
    {
      _4__pressed = true;
      interruption_hit_and_escape = true;
    }
    else if(key == '5')
    {
      _5__pressed = true;
      interruption_hit_and_escape = true;
      return;
    }
    else if(key == '6')
    {
      _6__pressed = true;
      interruption_hit_and_escape = true;
      return;
    }
    else if(key == '8')
    {
      _8__pressed = true;
      interruption_hit_and_escape = true;
      return;
    }
    else if(key == '9')
    {
      _9__pressed = true;
      interruption_hit_and_escape = true;
      return;
    }
}




void hit_and_escape(char key)
{
  interruption_hit_and_escape = false;
  FastLED.setBrightness(brightness);

  while(true)
  {
    for(int c = 0; c < 17; c++)
    {      
      int right_side = 0;
      int left_side = 0;
      int start_position = NUM_OF_LEDS / 2;
      int timer = 200;
  
      if(c != 2 && c != 7)
      {
        for(int i = 0; i < NUM_OF_LEDS / 2; i++)
        {
          leds[i] = array_colors[c];
          FastLED.show();
        }
        for(int i = NUM_OF_LEDS; i > NUM_OF_LEDS / 2; i--)
        {
          leds[i] = array_colors[c];
          FastLED.show();
        }
        leds[NUM_OF_LEDS / 2] = array_colors[c];
        FastLED.show();
        delay(500);
        // starting animation...
      
        while(right_side < 15)
        {
          for(int i = start_position; i >= NUM_OF_LEDS / 2 - right_side; i--)
          {
            
            key = keypad.getKey();
        
            control_brightness(key);
            interrupt_function_hit_and_escape(key);
      
            if(interruption_hit_and_escape)
            {
              return;
            }
            
            
            leds[i - 1] = array_colors[c];
            leds[i] = CRGB::Black;
            FastLED.show();
            delay(timer);
          }
      
          if(timer >= 45)
          {
            timer -= 15;
          }
          right_side += 1;
          start_position = NUM_OF_LEDS / 2 - right_side;
      
          if(right_side < 15)
          {
            for(int i = start_position; i <= NUM_OF_LEDS / 2 + left_side; i++)
            {

              key = keypad.getKey();
        
              control_brightness(key);
              interrupt_function_hit_and_escape(key);
        
              if(interruption_hit_and_escape)
              {
                return;
              }

              leds[i + 1] = array_colors[c];
              leds[i] = CRGB::Black;
              FastLED.show();
              delay(timer);
            }
            
            if(timer >= 45)
            {
              timer -= 15;
            }
            left_side += 1;
            start_position = NUM_OF_LEDS / 2 + left_side;
          }
        }
      
        for(int i = 0; i < NUM_OF_LEDS; i++)
        {

          key = keypad.getKey();
        
          control_brightness(key);
          interrupt_function_hit_and_escape(key);
      
          if(interruption_hit_and_escape)
          {
            return;
          }

            
          if(c + 1 == 2 || c + 1 == 7)
          {
            c++;
          }
          leds[i] = array_colors[c+1];
          FastLED.show();
          delay(40);
        }
      }
    }
  }
}



void X__switching_colors(char key)
{
  for(int i = 0; i < NUM_OF_LEDS; i++)
  {
    leds[i] = CRGB::Black;
    FastLED.show();
  }
  while(true)
  {
    for(int i = 0; i < 17; i++)
    {
      int right_side = 0;
      int left_side = NUM_OF_LEDS - 1;
      while(right_side < NUM_OF_LEDS)
      {
        key = keypad.getKey();
        control_brightness(key);

        if(key == '0')
        {
          _0__pressed = true;
          return;
        }
        else if(key == '1')
        {
          _1__pressed = true;
          return;
        }
        else if(key == '2')
        {
          _2__pressed = true;
          return;
        }
        else if(key == '3')
        {
          _3__pressed = true;
          return;
        }
        else if(key == '4')
        {
          _4__pressed = true;
          return;
        }
        else if(key == '5')
        {
          _5__pressed = true;
          return;
        }
        else if(key == '6')
        {
          _6__pressed = true;
          return;
        }
        else if(key == '7')
        {
          _7__pressed = true;
          return;
        }
        else if(key == '9')
        {
          _9__pressed = true;
          return;
        }
        leds[right_side++] = array_colors[i];
        leds[left_side--] = array_colors[i+2];
        FastLED.setBrightness(brightness);
        FastLED.show();
        delay(100);
      }
    }
  }
}






void sea_waves(char key)
{  
  FastLED.setBrightness(brightness);
  while(true)
  {
    key = keypad.getKey();
    control_brightness(key);

    if(key == '0')
    {
      _0__pressed = true;
      return;
    }
    
    else if(key == '1')
    {
      _1__pressed = true;
      return;
    }
        
    else if(key == '2')
    {
      _2__pressed = true;
      return;
    }
    else if(key == '3')
    {
      _3__pressed = true;
      return;
    }
    
    else if(key == '4')
    {
      _4__pressed = true;
      return;
    }
    else if(key == '5')
    {
      _5__pressed = true;
      return;
    }
    else if(key == '6')
    {
      _6__pressed = true;
      return;
    }
    else if(key == '7')
    {
      _7__pressed = true;
      return;
    }
    else if(key == '8')
    {
      _8__pressed = true;
      return;
    }
    
    for (int i = 0; i < NUM_OF_LEDS; i++) 
    {
      leds[i] = CHSV(166 , 255 , hue_sea_waves + (i * 10));
    }
    delay(6);
    hue_sea_waves++;
    FastLED.show();
    
    for (int i = 0; i < NUM_OF_LEDS; i++) 
    {
      leds[i] = CHSV(166 , 255 , hue_sea_waves - (i * 10));
    }
    delay(6);
    hue_sea_waves++;
    FastLED.show();
  }
}






void control_brightness(char key)
{
  if(key == '*' && brightness > 15)
  {
    brightness -= 15;
    FastLED.setBrightness(brightness);
    FastLED.show();
  }
      
  if(key == '#' && brightness < 255)
  {
    brightness += 15;
    FastLED.setBrightness(brightness);
    FastLED.show();
  }
}




void passcode()
{
  int digits = 0;
  int p = 0;
  char key;
  String PassCode = "";
  
  while(true)
  {
    if(digits < 5)
    {
      key = keypad.getKey();
      if(key == '0' || key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '*' || key == '#')
      {
        //Serial.println(key);
        for(int i = p; i < p + 6; i++)
        {
          FastLED.setBrightness(brightness);
          leds[i] = CRGB::Purple;
          FastLED.show();
        }
        p += 6;
        PassCode += key;
        digits++;
      }  
    }
    else
    {
      delay(300);
      if(PassCode == "02468") // Passcode: 02468
      {
        //Serial.println("Correct");
        for(int i = NUM_OF_LEDS; i >= 0; i--)
        {
          FastLED.setBrightness(brightness);
          leds[i] = CRGB::Black;
          FastLED.show();
        }
        for(int i = 0; i < NUM_OF_LEDS; i++)
        {
          FastLED.setBrightness(brightness);
          leds[i] = CRGB::Green;
          FastLED.show();
          delay(10);
        }
        delay(50);
        for(int i = NUM_OF_LEDS; i >= 0; i--)
        {
          FastLED.setBrightness(brightness);
          leds[i] = CRGB::Black;
          FastLED.show();
          delay(10);
        }
        break;
      }
      else
      {
        for(int i = NUM_OF_LEDS; i >= 0; i--)
        {
          FastLED.setBrightness(brightness);
          leds[i] = CRGB::Black;
          FastLED.show();
        }
        for(int i = 0; i < NUM_OF_LEDS; i++)
        {
          FastLED.setBrightness(brightness);
          leds[i] = CRGB::Red;
          FastLED.show();
          delay(10);
        }
        delay(50);
        for(int i = NUM_OF_LEDS; i >= 0; i--)
        {
          FastLED.setBrightness(brightness);
          leds[i] = CRGB::Black;
          FastLED.show();
          delay(10);
        }
        digits = 0;
        PassCode = "";
        p = 0;
      }
    }
  }
}





void loop()
{
  char key = keypad.getKey();

  control_brightness(key);
  /*if(key != NO_KEY)
  {
    Serial.println(key);
  }*/
  if(key == '1' || _1__pressed)
  {
    _1__pressed = false;
    pick_color( array_colors[ *pick_color_variable ] , brightness);

    if(*pick_color_variable < 16)
    {
      ++*pick_color_variable;
    }
    else
    {
     *pick_color_variable = 0;
    }
  }

  else if(key == '2' || _2__pressed)
  {
    _2__pressed = false;
    fade_in_fade_out( array_colors[ fade_variable ] , key , 0 , false);
  }
    
  else if(key == '3' || _3__pressed)
  {
     _3__pressed = false;

    fade_in_fade_out(array_colors[ fade_variable_with_colors ] , key , 16 , true);
  }

  else if(key == '4' || _4__pressed)
  {
    _4__pressed = false;
    fill_and_clear(array_colors[fill_and_clear_var] , key);
  }

  else if(key == '5' || _5__pressed)
  {
    _5__pressed = false;
    circle_RGB(key);
  }

  else if(key == '6' || _6__pressed)
  {
    _6__pressed = false;
    RGB_wave(key);
  }

  else if(key == '7' || _7__pressed)
  {
    _7__pressed = false;
    hit_and_escape(key);
  }

  else if(key == '8' || _8__pressed)
  {
    _8__pressed = false;
    X__switching_colors(key);
  }

  else if(key == '9' || _9__pressed)
  {
    _9__pressed = false;
    sea_waves(key);
  }

  else if(key == '0' || _0__pressed)
  {
    _0__pressed = false;
    for(int i = 0; i < NUM_OF_LEDS; i++)
    {
      leds[i] = CRGB::Black;
      FastLED.show();
    }
  }
}
