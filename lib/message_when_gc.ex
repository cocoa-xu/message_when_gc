defmodule MessageWhenGc do
  @moduledoc false

  def message_when_gc(pid, value) do
    MessageWhenGc.Nif.message_when_gc(pid, value)
    nil
  end
end
