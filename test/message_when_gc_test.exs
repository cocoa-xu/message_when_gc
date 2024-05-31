defmodule MessageWhenGcTest do
  use ExUnit.Case
  doctest MessageWhenGc

  test "greets the world" do
    assert MessageWhenGc.hello() == :world
  end
end
