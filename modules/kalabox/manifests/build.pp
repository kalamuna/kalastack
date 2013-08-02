/**
 *
 * runs apt-get update if applicable
 *
 */
class kalabox::build {

  file { "/etc/kalastack":
    ensure  => directory,
    mode    => 777,
    require => Class["user::config"],
  }

  file { "/etc/kalastack/aliases":
    ensure  => directory,
    mode    => 777,
    require => File["/etc/kalastack"],
  }

}
