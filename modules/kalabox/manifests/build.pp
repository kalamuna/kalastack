/**
 *
 * runs apt-get update if applicable
 *
 */
class kalabox::build {

  file { "/etc/kalastack":
    ensure  => directory,
    mode    => 777,
    owner   => $::kalauser,
    group   => $::kalauser,
  }

  File["/etc/kalastack"] -> Package <| |>

}
