# -*- mode: ruby -*-
# vi: set ft=ruby :

# Need to run some install tasks first
#
#   vagrant plugin install vagrant-hostsupdater
#   vagrant plugin install vagrant-vbguest # if you want to ensure guest addition parity
#
# This all needs to be run from the parent directory of kalastack

Vagrant.configure("2") do |config|
  # All Vagrant configuration is done here. The most common configuration
  # options are documented and commented below. For a complete reference,
  # please see the online documentation at vagrantup.com.
  # Wooden ships on the water. Very free. And Easy.

  # Every Vagrant virtual environment requires a box to build off of.
  # Use multi VM syntax
  
  # Generate a UUID to identify this box to the puppet master
  unless File.directory?(".kalabox")
    FileUtils.mkdir_p(".kalabox")
  end
  unless File.exist?(".kalabox/uuid")
    require 'securerandom'; 
    kalauuid = "kala." + SecureRandom.hex + ".box"
    File.new(".kalabox/uuid", 'w')
    File.open(".kalabox/uuid", "wb") do |file|
      file.write(kalauuid)
    end
  end
  
  config.vm.box = "kalabox"
  config.vm.hostname = File.read(".kalabox/uuid")

  # The url from where the 'config.vm.box' box will be fetched if it
  # doesn't already exist on the user's system.
  config.vm.box_url = "http://files.kalamuna.com/kalabox64.box"
  
  # Create a forwarded port mapping which allows access to a specific port
  # within the machine from a port on the host machine. In the example below,
  # accessing "localhost:8080" will access port 80 on the guest machine.
  # config.vm.network :forwarded_port, guest: 80, host: 8080

  # Create a private network, which allows host-only access to the machine
  # using a specific IP.
  config.vm.network :private_network, ip: "1.3.3.7"
  config.hostsupdater.aliases = ["kala", "start.kala", "php.kala", "grind.kala", "solr.kala"]

  # Create a public network, which generally matched to bridged network.
  # Bridged networks make the machine appear as another physical device on
  # your network.
  # config.vm.network :public_network

  # Share an additional folder to the guest VM. The first argument is
  # the path on the host to the actual folder. The second argument is
  # the path on the guest to mount the folder. And the optional third
  # argument is a set of non-required options.
  config.vm.synced_folder "~/kalabox/www", "/var/www", :create => true, :nfs => true
  config.vm.synced_folder "~/kalabox/drush", "/var/www/.drush", :create => true, :nfs => true

  # Set some SSH config
  # config.ssh.username = "kala"
  # config.ssh.host = "kalabox"
  # config.ssh.forward_agent = true

  # Provider-specific configuration so you can fine-tune various
  # backing providers for Vagrant. These expose provider-specific options.
  # Example for VirtualBox:
  #
  
  config.vm.provider :virtualbox do |vb|
  #   # Don't boot with headless mode
  #   vb.gui = true
  #
    # Use VBoxManage to customize the VM. For example to change memory:
    vb.customize ["modifyvm", :id, "--memory", "2048"]
    vb.name = "Kalabox"
  end
  #
  # View the documentation for the provider you're using for more
  # information on available options.

  # Enable provisioning with Puppet stand alone.  Puppet manifests
  # are contained in a directory path relative to this Vagrantfile.
  # You will need to create the manifests directory and a manifest in
  # the file precise64.pp in the manifests_path directory.
  #
  # An example Puppet manifest to provision the message of the day:
  #
  # # group { "puppet":
  # #   ensure => "present",
  # # }
  # #
  # # File { owner => 0, group => 0, mode => 0644 }
  # #
  # # file { '/etc/motd':
  # #   content => "Welcome to your Vagrant-built virtual machine!
  # #               Managed by Puppet.\n"
  # # }
  #
  
  config.vm.provision :puppet_server do |ps|
    ps.puppet_node = File.read(".kalabox/uuid")
    ps.puppet_server = "kalabox.kalamuna.com"
    ps.options = "--verbose --debug --test"
    ps.facter = {
      "vagrant" => "1",
      "kalauser" => "vagrant",
      "kalahost" => "1.3.3.7",
    }
  end
  # should not ever run this provisioner except for development
  config.vm.provision :puppet do |p|
     p.manifests_path = "manifests"
     p.manifest_file  = "site.pp"
     p.module_path = "modules"
     p.options = "--verbose --debug"
     p.facter = {
      "vagrant" => "1",
      "kalauser" => "vagrant",
      "kalahost" => "1.3.3.7",
    }
  end
  

  # Enable provisioning with chef solo, specifying a cookbooks path, roles
  # path, and data_bags path (all relative to this Vagrantfile), and adding
  # some recipes and/or roles.
  #
  # config.vm.provision :chef_solo do |chef|
  #   chef.cookbooks_path = "../my-recipes/cookbooks"
  #   chef.roles_path = "../my-recipes/roles"
  #   chef.data_bags_path = "../my-recipes/data_bags"
  #   chef.add_recipe "mysql"
  #   chef.add_role "web"
  #
  #   # You may also specify custom JSON attributes:
  #   chef.json = { :mysql_password => "foo" }
  # end

  # Enable provisioning with chef server, specifying the chef server URL,
  # and the path to the validation key (relative to this Vagrantfile).
  #
  # The Opscode Platform uses HTTPS. Substitute your organization for
  # ORGNAME in the URL and validation key.
  #
  # If you have your own Chef Server, use the appropriate URL, which may be
  # HTTP instead of HTTPS depending on your configuration. Also change the
  # validation key to validation.pem.
  #
  # config.vm.provision :chef_client do |chef|
  #   chef.chef_server_url = "https://api.opscode.com/organizations/ORGNAME"
  #   chef.validation_key_path = "ORGNAME-validator.pem"
  # end
  #
  # If you're using the Opscode platform, your validator client is
  # ORGNAME-validator, replacing ORGNAME with your organization name.
  #
  # If you have your own Chef Server, the default validation client name is
  # chef-validator, unless you changed the configuration.
  #
  #   chef.validation_client_name = "ORGNAME-validator"
  
  # Delete UUID when box is destroyed
  
  module VagrantPlugins
    module KUUID
      module Action
        class RemoveKUUID

          def initialize(app, env)
            @app = app
            @machine = env[:machine]
            @ui = env[:ui]
          end
  
          def call(env)
            machine_action = env[:machine_action]
            if machine_action == :destroy
              if File.exist?(".kalabox/uuid")
                File.delete(".kalabox/uuid")
                @ui.info "Removing UUID"
              end
            end
          end
  
        end
      end
    end
  end
  
  module VagrantPlugins
    module KUUID
      class Plugin < Vagrant.plugin('2')
        name 'KUUID'
        description <<-DESC
          This plugin removes the UUID on box destroy
        DESC
  
        action_hook("KUUID", :machine_action_destroy) do |hook|
          hook.append(Action::RemoveKUUID)
        end

      end
    end
  end
  
end
