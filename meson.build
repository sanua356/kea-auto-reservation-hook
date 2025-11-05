auto_reservation_lib = shared_library(
    'dhcp_auto_reservation',
    'lease4_select.cc',
    'auto_reservation_log.cc',
    'auto_reservation_messages.cc',
    'load_unload.cc',
    'version.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: HOOKS_PATH,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
auto_reservation_archive = static_library(
    'auto_reservation',
    objects: auto_reservation_lib.extract_all_objects(recursive: false),
)
