g++ -I. -I /usr/include/kea -L /usr/lib/kea/lib -fpic -shared -o auto_reservation.so \
  load_unload.cc lease4_select.cc version.cc auto_reservation_messages.cc auto_reservation_log.cc  \
  -lkea-dhcpsrv -lkea-dhcp -lkea-hooks -lkea-log -lkea-util -lkea-exceptions -lcurl
