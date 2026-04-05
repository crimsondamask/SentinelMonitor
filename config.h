#ifndef CONFIG_H
#define CONFIG_H

#define N_CHANNELS 1000
#define N_LINKS 5
#define POLL_URL "http://localhost:3000/api/get_links_config"
#define WRITE_TAG_URL "http://localhost:3000/api/write_tag"
#define RECONFIG_TAG_URL "http://localhost:3000/api/reconfigure_device_tag"
#define RECONFIG_DEVICE_PROTOCOL                                               \
  "http://localhost:3000/api/reconfigure_device_protocol"
#define RECONFIG_EVAL_URL "http://localhost:3000/api/reconfigure_eval"

enum TagValueType {
  ST_INT_VALUE,
  ST_REAL_VALUE,
  ST_BIT_VALUE,
};

struct SentinelTagValue {
  int type;
  float real_value;
  int int_value;
  int bit_value;
};
#endif // CONFIG_H
