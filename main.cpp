//
// Created by loki on 5/30/19.
//

#include <thread>

#include "nvhttp.h"
#include "stream.h"

extern "C" {
#include <rs.h>
}

#include "config.h"
#include "platform/common.h"
using namespace std::literals;
int main(int argc, char *argv[]) {
  if(argc > 1) {
    config::parse_file(argv[1]);
  }

  reed_solomon_init();

  std::thread httpThread { nvhttp::start };
  std::thread rtpThread { stream::rtpThread };

  httpThread.join();
  rtpThread.join();

  return 0;
}
