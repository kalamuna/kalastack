/**
 * Provides some custom git config
 */
class git::config {
  
  file { "/etc/gitconfig":
    ensure => file,
    mode   => 755,
    owner  => root,
    group  => root,
    source => "puppet:///modules/git/gitconfig",
  }

  file { "/etc/gitignore":
    ensure => file,
    mode   => 755,
    owner  => root,
    group  => root,
    source => "puppet:///modules/git/gitignore",
  }

  file { "/home/$::kalauser/.git-completion.bash":
    ensure => file,
    mode   => 755,
    owner  => $::kalauser,
    group  => $::kalauser,
    source => "puppet:///modules/git/.git-completion.bash",
  }
    
}