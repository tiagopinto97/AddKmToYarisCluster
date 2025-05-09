Project created to save the simple sketch made to add the missing mileage to my speedometer after I bought a used replacement that had about less 70000 km.


I used an Arduino leonardo + a CAN-BUS_Shield_V2.0 and used the base examples from the Seeed_Arduino_CAN library to read the car current data and to send the data.

This specific sketch is optimized to make the most amount of mileage in the least ammount of time. It can add about 1km per 4 secconds, making it so I only need about 3 days to get to the desired mileage.

I can't really explain how it works other than I detected that the 0xB4 message updated the speedometer reading, however it did not change the mileage. While doing some tests with intervals and slight different messages I saw the odometer increase and I just kept optimizing to the max I could.

It also has rpm code commented, it's a bit ugly but I might want to use at a latter time with simhub and a canbus capable cluster instead of my current broken e36 one. So one can dream for now :).

To make the mileage not increase the odometer  comment one of the sendCANMessage, the issue should be having the same bits at the start of the data.
