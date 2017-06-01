# CPE329FinalProject
Hot liquid temperature sensor

In principle, this system is a coffee temperature sensor. To use the system, the end of the 
sensor must be inserted into the coffee cup and held there for a few seconds as it takes the 
sensor some time (170 ms at maximum) to detect the temperature of its environment. If 
the sensor detects that the temperature of the coffee falls within the pre-programmed 
range of temperatures considered acceptable for drinkable coffee then a buzzer will 
sound, alerting the user that their coffee is the proper temperature. If the coffee’s 
temperature is not within this pre-programmed range then the coffee’s temperature will 
be displayed on an LCD screen, so the user knows if they need to warm or cool their 
coffee to bring it into the proper temperature range. Lastly, the totality of the system will 
be battery powered, as maintaining the MSP432’s laptop-based power connection near 
liquids is not a particularly safe idea, and packaged in some sort of self-containing 
fashion. Additionally, it is important to note that the temperature sensor interfaces with 
the MSP432 using 1-wire SPI. While traditional SPI requires 3 wires (CS, Data_In, and 
SCLK), 1-wire SPI uses a series of switches to generate these signals from the Data input 
signal. This is diagrammed below in a figure borrowed from the data sheet of the 
waterproof temperature sensor.
