idf_component_register(SRCS "init.c" "console.c" "dnd.c" "dndv_comms.c" "dndv_data.c" "dndv_internals.c" "dndv_log.c" "dndv_sync.c" "dndv_ui.c"
                    INCLUDE_DIRS ".")
 
SET(SOURCES ui/screens/ui_Screen1.c
ui/ui.c
ui/ui_helpers.c)

add_library(ui ${SOURCES})