
class git {

  include git::params

  package { $git::params::packages:
    ensure => present,
  }
}
