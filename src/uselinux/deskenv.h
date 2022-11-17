#ifndef DESKENV_H
#define DESKENV_H

struct uselinux_de {
  const char* string;
  void (*responder)(void);
};

/**
 * @brief React to a desktop environment supplied by the user.
 *
 * @param desk Name of desktop environment. Case insensitive.
 */
void desktop_environments(char *desk);

/**
 * @brief Redirect a single coolant source to stop the CPU from
 * overheating.
 * 
 * @param i ID of coolant source
 * @return int Whether the coolant was successfully redirected
 */
int redirect_one_coolant_source(int i);

/**
 * @brief Redirect several coolant sources
 * 
 * @param coolant_sources Number of available sources
 * @param required Redirected sources required to avert overheating
 * @return int Whether enough coolant sources were activated
 */
int redirect_coolant_sources(int coolant_sources, int required);

/**
 * @brief Activate cooling system routines to stop GNOME from "overheating"
 * the computer
 */
void desktop_environment_gnome_cooling_sys();

/**
 * @brief Respond if user supplies "gnome" to --desk option
 */
void desktop_environment_gnome();

/**
 * @brief Respond if user supplies "kde" to --desk option
 */
void desktop_environment_kde();

/**
 * @brief Respond to the --desk option and call a function depending on the
 * desktop enviroment provided
 */
void desktop_environments(char *desk);

#endif /* DESKENV_H */
