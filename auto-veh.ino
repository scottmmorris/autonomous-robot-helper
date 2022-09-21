// ultrasonic control pins
#define trigPinDown 13
#define echoPinDown 12
#define trigPinForward 8
#define echoPinForward 7

// motor control pins
#define in1 2
#define in2 3
#define in3 4
#define in4 5

void setup() {
  Serial.begin (9600);
  pinMode(trigPinDown, OUTPUT);
  pinMode(echoPinDown, INPUT);
  pinMode(trigPinForward, OUTPUT);
  pinMode(echoPinForward, INPUT);

  digitalWrite(trigPinDown, LOW);
  digitalWrite(trigPinForward, LOW);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void loop() {
  long distance_forward, distance_down;
  distance_forward = calculate_distance(trigPinForward, echoPinForward);
  distance_down = calculate_distance(trigPinDown, echoPinDown);
   if (distance_forward <= 5 || distance_down > 3) {
    Serial.println("Obstacle or cliff detected");
    
    // reverse the left motor and wait
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    delayMicroseconds(1000);

    // return the motor to forward direction
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  Serial.print("F: ");
  Serial.print(distance_forward);
  Serial.print(" cm, D: ");
  Serial.print(distance_down);
  Serial.println(" cm");

  delay(500);
}

long calculate_distance(int trig_pin, int echo_pin) {
  long duration;
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  return (duration / 2) / 29.1;
}
