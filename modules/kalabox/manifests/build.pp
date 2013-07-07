/**
 *
 * runs apt-get update if applicable
 *
 */
class kalabox::build {

  file { "/etc/kalastack":
    ensure  => directory,
    mode    => 777,
    owner   => 501,
    group   => dialout,
    require => Class["user::config"],
  }

}
