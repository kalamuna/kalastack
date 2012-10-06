
class mysql::client::install {
  package { "mysql-client":
    ensure   => present,
  }
}

class mysql::client {
  include mysql::client::install
}
