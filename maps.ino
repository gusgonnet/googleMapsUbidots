#include <google-maps-device-locator.h>

// NOTE: localData.h should contain the ubidots token in this form:
// This value comes from ubidots -> menu -> API keys -> Authentication token
// #define UBIDOTS_TOKEN "skljfhsakldjdfh29841283840922324"
// Alternatively, do not create localData.h, remove line 8 below 
// and define UBIDOTS_TOKEN in the current file
#include "localData.h"

/*******************************************************************************
 ubidots variables

 webhook definition:
  Event name: ubidotsLatLong
  url: https://things.ubidots.com/api/v1.6/devices/{{ubi-dsl-vl}}/values/?token={{ubi-token}}
  Request type: POST
  Device: Any
  Advanced settings:
  Send custom data: JSON  
  and then enter:

    {
      "value": "{{ubi-value}}",
      "context": {
        "lat": " {{google-lat}}",
        "lng": "{{google-lng}}"
      }
    }
          
  include default data: no
  enforce ssl: yes
*******************************************************************************/
// This value comes from ubidots
const String ubidotsToken = UBIDOTS_TOKEN;


GoogleMapsDeviceLocator locator;

#define APP_NAME "googleMaps"
String VERSION = "Version 0.01";
/*******************************************************************************
 * changes in version 0.01:
       * Initial version
*******************************************************************************/


SYSTEM_MODE(AUTOMATIC);

void setup()
{
  Particle.publish(APP_NAME, VERSION, PRIVATE);

  // Scan for visible networks and publish to the cloud every 30 seconds
  // Pass the returned location to be handled by the locationCallback() method
  locator.withSubscribe(locationCallback).withLocatePeriodic(60);
}

void loop() {
  locator.loop();
}

void locationCallback(float lat, float lon, float accuracy) {
  // Handle the returned location data for the device. This method is passed three arguments:
  // - Latitude
  // - Longitude
  // - Accuracy of estimated location (in meters)
  
  String name = "geo";
  String value = "1"; //dummy value

  Particle.publish("ubidotsLatLong", "{\"ubi-dsl-vl\":\"" + Particle.deviceID() + "/" + name + "\", \"ubi-token\":\"" + ubidotsToken + "\", \"ubi-value\":\"" + value + "\" , \"google-lat\":\"" + lat + "\" , \"google-lng\":\"" + lon + "\"}", 60, PRIVATE);
}

