size_t const bufferSize = 100;
char buffer[bufferSize + 1];                    //This means that if your buffer has been filled to 100 (0-99) and then there is a carriage return, when you enter the PARSE function, nothing freaks out (it doesn't try buffer[101] = 0)
unsigned int length = 0;

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
}

void parse(){
  buffer[length] = 0;                            //null terminate the string (append a zero)
  if(strcmp(buffer, "ledon") == 0){              //if the string contained within the buffer is identical to "ledon"
    digitalWrite(2, HIGH);
    Serial.write(buffer);
  }
  if(strcmp(buffer, "ledoff") == 0){
    digitalWrite(2, LOW);
    Serial.write(buffer);
  }
}

void loop() {
  while(Serial.available() > 0){                //while there are bytes that are available to be read on the serial port
    auto incomingByte = Serial.read();          //read a byte into this variable (auto is just like var in other languages, an undefined variable)
    if(incomingByte == '$'){                    //starting your commands with a '$' means that you can retype commands and avoid corruption. You need the single quotes here because of how "" and '' are handled in some languages.
      length = 0;                               //In C (along with some others) using '' translates to a character 1  byte (8 bits) long, so just '$'. If you used "$", then it gets null terminated and becomes 2 bytes long ("$0").
    }
    else if(incomingByte == '\r'){              //this checks if carriage return has been sent
      parse();                                  //calling our parse function which is just checking which command has been sent
      length = 0;
    }
    else {
      if(length < bufferSize){                  //this stops you adding chars when you are going to exceed the length of your buffer
        buffer[length] = incomingByte;          //if you have space left in your buffer, add the incoming byte to the next space
        length++; 
         }
    }
  }
}
