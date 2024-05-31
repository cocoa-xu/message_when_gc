# MessageWhenGc

A proof of concept project: NIF returns a reference (an `enif_make_resource_binary`) that sends a message to `pid` with `value` once the resource is GCed.

## Installation

```elixir
iex> Mix.install([{:message_when_gc, github: "cocoa-xu/message_when_gc"}])
```

## Test

```elixir
iex> MessageWhenGc.message_when_gc(self(), "hello")
nil
iex> receive do msg -> IO.puts("Received message: #{inspect(msg)}") end
destruct_message is called, send value to pid
destruct_message end
Received message: "hello"
:ok
```
