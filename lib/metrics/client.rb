module Metrics
  class Client
    attr_accessor :socket
    attr_reader :username, :access_token

    def initialize(username, access_token, opts={})
      @host = opts[:host] || 'localhost'
      @port = opts[:port] || '8080'

      @username = username
      @access_token = access_token
    end

    def connect!
      self.socket ||= WebSocket.new("ws://#{@host}:#{@port}")
    end

    def authenticate!
      connect!
      send(username: username, access_token: access_token)
    end

    def incr(key)
      send(op: 'incr', key: key)
    end

    def decr(key)
      send(op: 'decr', key: key)
    end

    def report(key, value, reported_at = Time.now)
      send(key: key, value: value, reported_at: reported_at)
    end

    def connected?
      return false if self.socket.nil?
      ping
    end

    def self.create(username, access_token)
      client = Client.new(username, access_token)
      client.authenticate!
      client
    end

    private
    def send(msg={})
      self.socket.send(msg.to_json)

      response = self.socket.receive
      JSON.parse(response)
    end

    def ping
      val = Time.now.to_i
      response = self.send(ping: val)
      response[:pong] == val
    end
  end
end
