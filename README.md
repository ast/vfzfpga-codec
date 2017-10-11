# vfzfpga-codec

Work in progress (still not functional) ALSA SoC CODEC for use with custom FPGA based codec we are developing
for use in a Software Defined Radio.

We are also developing a Linux Kernel Module to control the board.

# Background

We are developing an FPGA based Software Defined Radio transceiver for amateur radio. Demodulation is done
in the FPGA and samples are sent to a voice band codec with integrated amplifier.

It was also desirable to transfer
a digital copy of demodulated samples for digital mode operation and remote operation. For this we decided to
use the i2s bus to transfer samples to a Raspberry Pi.

The default Linux Drivers did not support arbitrary sample rate (we use 39ksps) so slight modifications had to be done to two
files. Check `patched/` for details.

After these modifications the FPGA works great operating as clk & FRM master (`SND_SOC_DAIFMT_CBM_CFM`)

This repository reflects my struggles in writing a dedicated ASoC CODEC driver for the FPGA.


* FPGA: Altera Cyclone IV
* ADC: Analog Devices AD7760.
* Voice Band CODEC: TI TLV320AIC20K
* DAC: TI DAC5672

# More information

* [Linux Kernel Module](https://github.com/ast/vfzsdr)
* [FPGA firmware and information](https://github.com/danupp/fpgasdr)
* [SM6VFZ's blog](https://sm6vfz.wordpress.com)
* [Receiving Grimeton Radio SAQ on 17kHz(!!)](https://www.youtube.com/watch?v=jcrzIcjE5D8)

# Contributors

* Albin, SM6WJM
* Daniel, SM6VFZ
