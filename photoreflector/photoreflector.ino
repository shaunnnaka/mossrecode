const int ANALOG_PIN = A0;
const int SPEAKER_PIN = 9;
const int SAMPLE_SIZE = 10; // 移動平均のサンプル数
int sampleBuffer[SAMPLE_SIZE]; // 移動平均のための配列
int sampleIndex = 0; // サンプルバッファのインデックス
int filteredValue = 0; // 移動平均された値

void setup() {
  Serial.begin(9600);
  pinMode(SPEAKER_PIN, OUTPUT);
}

void loop() {
  // アナログ値を取得し、サンプルバッファに追加する
  int rawValue = analogRead(ANALOG_PIN);
  sampleBuffer[sampleIndex] = rawValue;
  sampleIndex = (sampleIndex + 1) % SAMPLE_SIZE;

  // サンプルバッファの平均値を計算する
  int sum = 0;
  for (int i = 0; i < SAMPLE_SIZE; i++) {
    sum += sampleBuffer[i];
  }
  filteredValue = sum / SAMPLE_SIZE;

  // アナログ値が600以上の場合は無音
  if (filteredValue >= 600) {
    noTone(SPEAKER_PIN);
    return;
  }

//  // アナログ値を0-255の範囲に変換し、PWM値として設定する
//  int pwmValue = map(filteredValue, 300, 600, 0, 255);
//  analogWrite(SPEAKER_PIN, pwmValue);

  // アナログ値に応じて周波数を設定する
  int frequency = map(filteredValue, 300, 600, 50, 3000);
  tone(SPEAKER_PIN, frequency);

  delay(100); // 10ms待機
}
