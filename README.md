# misc-testing

## Notes on how the system will work

So, the idea is to have three arduinos: one that makes the noise, one that provides a signal, and one that recieves the signal. The noise arduino will output the noise via a DAC breakout, to allow for more possible values. This will be combined with a signal coming from the signal arduino in the noisy circuit, which will output a signal readable by the reciever arduino. The noisy arduino will also be hooked up to the DIP, where a user can change its value to select different experiment configurations. The noise arduino will also connect directly to the signal arduino to configure it for the experiment as well. For example, one switch configuration could change the type of noise being output, or what message the signal arduino is making. There will also be a potentiometer connected to the noise arduino, which will control the SNR of the noise output. The user will have access to just the pot, the dips, and the USB ports on the signal and receiver arduinos for connection to matlab. The user will also need to connect the 12 wall wart.

## making noise
the noise arduino code, as it stands now, is `noise-generation.ino`. See [this](https://learn.sparkfun.com/tutorials/mcp4725-digital-to-analog-converter-hookup-guide) for hookups. It's currently written to make uniform noise. 
