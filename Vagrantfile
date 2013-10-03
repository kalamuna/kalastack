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

  # Load correct config JSON
  default_conf_path = File.expand_path(File.dirname(__FILE__)) + "/default.config.json"
  conf = JSON.parse(File.read(default_conf_path))
  # Merge in any custom settings
  if File.exist?(File.expand_path(File.dirname(__FILE__)) + "/config.json")
    conf.merge!(JSON.parse(File.read(File.expand_path(File.dirname(__FILE__)) + "/config.json")))
  end

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

  # Some basic vm config
  config.vm.box = conf["boxname"]
  config.vm.hostname = File.read(".kalabox/uuid")

  # Gather some more data about the host machine - this is only tested on mac
  hostarch = %x[ uname -m ].strip
  hostker = %x[ uname ].strip
  if hostker == "Darwin" then #looking for way to strip newline
    hostmem = Integer(%x[ sysctl hw.memsize ].scan(/\d+/).shift) / 1049000
  elsif hostker == "Linux" then
    hostmem = Integer(%x[ grep MemTotal /proc/meminfo ].scan(/\d+/).shift) / 1024
  else
    hostmem = conf["default_memory"]
  end

  # Set a hard maximum on memsize
  # This should translate to a 3GB MAXBOX
  if hostmem > 12288 then
    hostmem = 12288
  elsif hostmem < 4096 then
    puts "WARNING: Kalabox is designed to work best with at least 4096MB of RAM! You have #{ hostmem }MB."
  end

  # The url from where the 'config.vm.box' box will be fetched if it
  # doesn't already exist on the user's system.
  if hostarch.include? "64" then
    config.vm.box_url = conf["box_location"]["64"]
  else
    config.vm.box_url = conf["box_location"]["32"]
  end

  # Create a private network, which allows host-only access to the machine
  # using a specific IP.
  config.vm.network :private_network, ip: conf["ip"]
  config.hostsupdater.aliases = conf["host_entries"]

  # Share an additional folder to the guest VM. The first argument is
  # the path on the host to the actual folder. The second argument is
  # the path on the guest to mount the folder. And the optional third
  # argument is a set of non-required options.
  config.vm.synced_folder Dir.home + conf["synced_www_folder"]["host_path"], conf["synced_www_folder"]["guest_path"], :create => conf["synced_www_folder"]["create"], :nfs => conf["synced_www_folder"]["nfs"], :nfs_version => conf["synced_www_folder"]["nfs_version"]
  config.vm.synced_folder Dir.home + conf["synced_alias_folder"]["host_path"], conf["synced_alias_folder"]["guest_path"], :create => conf["synced_alias_folder"]["create"], :nfs => conf["synced_alias_folder"]["nfs"], :nfs_version => conf["synced_alias_folder"]["nfs_version"]

  # Set some SSH config
  config.ssh.forward_agent = conf["ssh_forwarding"]

  # Provider-specific configuration so you can fine-tune various
  # backing providers for Vagrant. These expose provider-specific options.
  # Example for VirtualBox:

  config.vm.provider :virtualbox do |vb|
  #   # Don't boot with headless mode
  #   vb.gui = true
  #
    # Use VBoxManage to customize the VM. For example to change memory:
    vb.customize ["modifyvm", :id, "--memory", (hostmem / conf["memory_divisor"].to_i)]
    vb.name = File.read(".kalabox/uuid")
  end
  #
  # View the documentation for the provider you're using for more
  # information on available options.

  # Use the correct provisioner based on some environmental settings
  if ENV['KALABOX_DEV']=='TRUE' then
   config.vm.provision :puppet do |p|
     p.manifests_path = "manifests"
     p.manifest_file  = "site.pp"
     p.module_path = "modules"
     p.options = "--verbose --debug"
     p.facter = {
      "vagrant" => "1",
      "kalauser" => conf["boxuser"],
        "kalahost" => conf["host_ip"],
      "kalamem" => (hostmem / conf["memory_divisor"].to_i),
    }
    end
  elsif ENV['KALABOX_SOLR']=='TRUE' then
    config.vm.provision :puppet do |p|
      p.manifests_path = "manifests"
      p.manifest_file  = "solr.pp"
      p.module_path = "modules"
      p.options = "--verbose --debug"
      p.facter = {
        "vagrant" => "1",
        "kalauser" => conf["boxuser"],
        "kalahost" => conf["host_ip"],
        "kalamem" => (hostmem / conf["memory_divisor"].to_i),
      }
    end
  else
    config.vm.provision :puppet_server do |ps|
      ps.puppet_node = File.read(".kalabox/uuid")
      ps.puppet_server = conf["puppet_master"]["server"]
      ps.options = "--verbose --debug --test"
      ps.facter = {
        "vagrant" => "1",
        "kalauser" => conf["boxuser"],
        "kalahost" => conf["host_ip"],
        "kalaversion" => conf["version"],
        "kalamem" => (hostmem / conf["memory_divisor"].to_i),
      }
    end
  end

  # Here are some faux plugins that we are using to perform various operations
  # like making sure an SSH key exists and is forwarded, deleting the UUID on destroy
  # and making sure the puppet master is awake

  # Delete UUID when box is destroyed
  module VagrantPlugins
    module KBOX
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

        class WakeMaster

          def initialize(app, env)
            @app = app
            @machine = env[:machine]
            @ui = env[:ui]
          end

          def call(env)
            machine_action = env[:machine_action]
            if machine_action == :up
              require 'open-uri'
              @ui.info "Making sure puppet master is awake"
              begin
                contents = open('http://foreman.kalamuna.com') {|io| io.read}
              rescue Exception => e
                @ui.info "Error connecting to puppet master"
                ENV['KALABOX_DEV'] = 'TRUE'
              end

            end
            @app.call(env)
          end
        end

        class Kalassh

          def initialize(app, env)
            @app = app
            @machine = env[:machine]
            @ui = env[:ui]
          end

          def call(env)
            machine_action = env[:machine_action]
            if machine_action == :up
              unless File.exist?(Dir.home + "/.ssh/id_rsa") && File.exist?(Dir.home + "/.ssh/id_rsa.pub")
                %x[ ssh-keygen -b 2048 -t rsa -f #{ Dir.home }/.ssh/id_rsa -q -N "" ]
                @ui.info "Creating a ssh key"
              end
              %x[ ssh-add -k ]
              @ui.info "Forwarding in your SSH key"
            end
            @app.call(env)
          end
        end
      end
    end
  end

  module VagrantPlugins
    module KBOX
      class Plugin < Vagrant.plugin('2')
        name 'KBOX'
        description <<-DESC
          This plugin does some kalabox stuff
        DESC

        action_hook("RemoveUUID", :machine_action_destroy) do |hook|
          hook.append(Action::RemoveKUUID)
        end

        action_hook("WakeMaster", :machine_action_up) do |hook|
          hook.prepend(Action::WakeMaster)
        end

        action_hook("Kalassh", :machine_action_up) do |hook|
          hook.prepend(Action::Kalassh)
        end

      end
    end
  end

end
