import processing.serial.*;

Serial myPort;  // 定義序列埠物件
float[] axData, ayData, azData, gxData, gyData, gzData;  // 儲存數據
int maxDataPoints = 100;  // 顯示的數據點數量

void setup() {
  size(1000, 800);  // 設定視窗大小
  myPort = new Serial(this, Serial.list()[0], 9600);  // 連接第一個序列埠
  myPort.bufferUntil('\n');  // 每當接收到換行符時讀取數據

  // 初始化數據陣列
  axData = new float[maxDataPoints];
  ayData = new float[maxDataPoints];
  azData = new float[maxDataPoints];
  gxData = new float[maxDataPoints];
  gyData = new float[maxDataPoints];
  gzData = new float[maxDataPoints];
  background(0);
}

void draw() {
  background(255);  // 清空畫面
  stroke(0); fill(0);
  textSize(16);
  text("MPU6050 Real-Time Data Visualization", 10, 20);

  // 繪製折線圖
  drawGraph(axData, color(255, 0, 0), 0);  // X-axis in red
  drawGraph(ayData, color(0, 255, 0), 70); // Y-axis in green
  drawGraph(azData, color(0, 0, 255), 140); // Z-axis in blue
  drawGraph(gxData, color(193, 240, 188), 210); 
  drawGraph(gyData, color(255, 102, 178), 280); 
  drawGraph(gzData, color(136, 183, 245), 350); 
}

void drawGraph(float[] data, color lineColor, float yOffset) {
  // 筆刷顏色
  stroke(lineColor);
  noFill();
  beginShape();
  for (int i = 0; i < data.length; i++) {
    float x = map(i, 0, data.length, 0, width);
    float y = map(data[i], -32768, 32768, height / 2, 0) + yOffset;
    vertex(x, y);
  }
  endShape();
}
void serialEvent(Serial myPort) {
  String rawData = myPort.readStringUntil('\n');  // 讀取數據
  if (rawData != null) {
    println("Received: " + rawData);  // 除錯資訊
    rawData = trim(rawData);
    String[] values = split(rawData, '\t');  // 分割數據

    if (values.length == 6) {
      shiftArray(axData, float(values[0]));
      shiftArray(ayData, float(values[1]));
      shiftArray(azData, float(values[2]));
      shiftArray(gxData, float(values[3]));
      shiftArray(gyData, float(values[4]));
      shiftArray(gzData, float(values[5]));
    }
  }
}

// 將陣列向左移動，並插入新數據
void shiftArray(float[] array, float newValue) {
  for (int i = 0; i < array.length - 1; i++) {
    array[i] = array[i + 1];
  }
  array[array.length - 1] = newValue;
}
