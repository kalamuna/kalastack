/**
 *
 * Installs drush and provides some custom commands
 *
 */
class frontend {

  include frontend::prepare, frontend::install, frontend::packages

}
