/**
 * 
 * Provides some custom cnfig
 * 
 */
class user::config {
    
    file { "/home/$::kalauser/.gitconfig":
      ensure  => file,
      mode    => 755,
      owner   => $::kalauser,
      group   => $::kalauser,
      source  => "puppet:///modules/user/.gitconfig",
    }
    
    file { "/home/$::kalauser/.gitignore":
      ensure  => file,
      mode    => 755,
      owner   => $::kalauser,
      group   => $::kalauser,
      source  => "puppet:///modules/user/.gitignore",
    }
    
    file { "/home/$::kalauser/.aliases":
      ensure  => file,
      mode    => 755,
      owner   => $::kalauser,
      group   => $::kalauser,
      source  => "puppet:///modules/user/.aliases",
    }
    
    file { "/home/$::kalauser/.colors":
      ensure  => file,
      mode    => 755,
      owner   => $::kalauser,
      group   => $::kalauser,
      source  => "puppet:///modules/user/.colors",
    }
    
    file { "/home/$::kalauser/.exports":
      ensure  => file,
      mode    => 755,
      owner   => $::kalauser,
      group   => $::kalauser,
      source  => "puppet:///modules/user/.exports",
    }
    
    file { "/home/$::kalauser/.bashrc":
      ensure  => file,
      mode    => 755,
      owner   => $::kalauser,
      group   => $::kalauser,
      source  => "puppet:///modules/user/.bashrc",
    }
    
    file { "/home/$::kalauser/.mallis_money":
      ensure  => file,
      mode    => 755,
      owner   => $::kalauser,
      group   => $::kalauser,
      source  => "puppet:///modules/user/.mallis_money",
    }
    
    file { "/home/$::kalauser/.git-completion.bash":
      ensure  => file,
      mode    => 755,
      owner   => $::kalauser,
      group   => $::kalauser,
      source  => "puppet:///modules/user/.git-completion.bash",
    }
    
}