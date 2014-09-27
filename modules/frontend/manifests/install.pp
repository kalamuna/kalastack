/**
 *
 * Installs drush
 *
 */
class frontend::install {

  package { "nodejs":
    ensure   => present,
    require => Class["frontend::prepare"],
  }

}
