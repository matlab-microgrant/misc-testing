//Purpose of POC?
float pdf(const float &x) {
  return 1 / sqrtf(2 * M_PI) * exp(-x * x * 0.5);
}
int nbins = 32; //what does this stand for?
float minBound = -5;
float maxBound = 5;

float cdf[33]; //what does this stand for
float dx = (maxBound - minBound) / nbins;
float sum = 0;


void setup() {
  cdf[0] = 0.f;
  //what is this loop for?
  for (int n = 1; n < nbins; n++) {
    float x = minBound + (maxBound - minBound) * (n / (float)(nbins));
    float pdf_x = pdf(x) * dx;
    cdf[n] = cdf[n - 1] + pdf_x;
    sum += pdf_x;
  }
  cdf[nbins] = 1;
//what is this loop for?
  float r = random(1024) / 1023.0;
  int index = 0;
  float lower_value = 0;
  for (int i = 1; i < nbins; i++) {
    if (cdf[i] > r){
        index = i;
        lower_value = cdf[i - 1];
      } 
  }
}

void loop() {

}
