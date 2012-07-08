# encoding: utf-8

require 'rubygems'
require 'bundler'
begin
  Bundler.setup(:default, :development)
rescue Bundler::BundlerError => e
  $stderr.puts e.message
  $stderr.puts "Run `bundle install` to install missing gems"
  exit e.status_code
end
require 'rake'

require 'jeweler'
Jeweler::Tasks.new do |gem|
  # gem is a Gem::Specification... see http://docs.rubygems.org/read/chapter/20 for more options
  gem.name = "metrics"
  gem.homepage = "http://github.com/bradhe/metrics-client"
  gem.license = "MIT"
  gem.summary = %Q{Push data to Metrics}
  gem.description = %Q{Client for pushing data to Metrics}
  gem.email = "brad@cloudability.com"
  gem.authors = ["Brad Heller"]
  gem.extensions = %w(ext/metrics/extconf.rb)
  # dependencies defined in Gemfile
end
Jeweler::RubygemsDotOrgTasks.new
