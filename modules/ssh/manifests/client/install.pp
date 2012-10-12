class ssh::client::install {
    package { "openssh-client":
        ensure => latest,
    }
}
