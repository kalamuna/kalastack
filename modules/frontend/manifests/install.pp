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

  package { "ruby2.0":
    ensure   => present,
    require => Class["frontend::prepare"],
  }

  package { "ruby2.0-dev":
    ensure   => present,
    require => Class["frontend::prepare"],
  }

  exec { "setnewruby":
    unless  => "ruby -v | grep 2.0.0",
    path    => "/bin:/usr/bin",
    command => "sudo update-alternatives --install /usr/bin/ruby ruby /usr/bin/ruby2.0 400",
    require => Package["ruby2.0"],
  }

}
