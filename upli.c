#include <stdio.h>

#include <upnp/upnp.h>

static UpnpClient_Handle handle = -1;

static int
event_handler(
    Upnp_EventType type, const void *event, void *cookie)
{
  if (type != UPNP_DISCOVERY_SEARCH_RESULT)
    return 0;

  const UpnpDiscovery *discovery = event;
  printf("%s\n", UpnpDiscovery_get_DeviceID_cstr(discovery));
  printf("%s\n", UpnpDiscovery_get_Location_cstr(discovery));

  return 1;
}

int
main()
{
  int status;
  unsigned short port = 0;
  char *ip_address = NULL;

  status = UpnpInit2(ip_address, port);
  if (status != UPNP_E_SUCCESS) {
    fprintf(stderr, "Init2 %d\n", status);
  }

  status = UpnpRegisterClient(event_handler, &handle, &handle);
  if (status != UPNP_E_SUCCESS) {
    fprintf(stderr, "RegisterClient %d\n", status);
  }

  status = UpnpSearchAsync(handle, 10, "urn:schemas-upnp-org:device:MediaServer:1", NULL);
  if (status != UPNP_E_SUCCESS) {
    fprintf(stderr, "SearchAsync %d\n", status);
  }

  for (;;);

  UpnpFinish();

  return 0;
}
