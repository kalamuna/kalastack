/**
 *
 * Installs drush and provides some custom commands
 *
 */
class drush {

  include drush::composer, drush::install, drush::config, drush::terminatur, drush::refresh

}
