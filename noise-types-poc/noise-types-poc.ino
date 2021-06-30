template<class ForwardIt, class T>
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value)
{
    ForwardIt it;
    typename std::iterator_traits<ForwardIt>::difference_type count, step;
    count = std::distance(first, last);
 
    while (count > 0) {
        it = first; 
        step = count / 2; 
        std::advance(it, step);
        if (*it < value) {
            first = ++it; 
            count -= step + 1; 
        }
        else
            count = step;
    }
    return first;
}
float pdf(const float &x) {
  return 1 / sqrtf(2 * M_PI) * exp(-x * x * 0.5);
}
float sample(float *cdf, const uint32_t &nbins, const float &minBound, const float &maxBound)
{
  float r = random(1,500)/100.0;
  float *ptr = lower_bound(cdf, cdf + nbins + 1, r);
  int off = std::max(0, (int)(ptr - cdf - 1));
  float t = (r - cdf[off]) / (cdf[off + 1] - cdf[off]);
  float x = (off + t) / (float)(nbins);
  return minBound + (maxBound - minBound) * x;
}

srand48(13); // seed random generator
// create CDF
int nbins = 32;
float minBound = -5, maxBound = 5;
float cdf[nbins + 1], dx = (maxBound - minBound) / nbins, sum = 0;
cdf[0] = 0.f;
for (int n = 1; n < nbins; ++n) {
  float x = minBound + (maxBound - minBound) * (n / (float)(nbins));
  float pdf_x = pdf(x) * dx;
  cdf[n] = cdf[n - 1] + pdf_x;
  sum += pdf_x;
}

cdf[nbins] = 1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float diff = sample(cdf, nbins, minBound, maxBound); // random var between -5 and 5 
  Serial.println(diff);
}
