#include "SSDP.h"
#include <ESP32SSDP.h>
#include "Settings.h"

void QSSDP::begin()
{
	SSDP.setDeviceType("urn:qvex.eu:device:LedStripController:1");
	SSDP.setSchemaURL("description.xml");
	SSDP.setHTTPPort(80);
	SSDP.setName("QVEX Controller - "+DEVICE_NAME);
	SSDP.setSerialNumber("001788102201");
	SSDP.setModelName("QVEX LED strip controller 0.9");
	SSDP.setModelNumber("929000226503");
	SSDP.setModelURL("http://www.qvex.eu");
	SSDP.setManufacturer("QVEX Tech");
	SSDP.setManufacturerURL("http://www.qvex.eu");
  	SSDP.begin();
  	Serial.println("SSDP: ok");
}

void QSSDP::schema(WiFiClient c)
{
	SSDP.schema(c);
}
