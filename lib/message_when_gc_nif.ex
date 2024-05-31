defmodule MessageWhenGc.Nif do
  @on_load :load_nif

  def load_nif do
    nif_file = ~c"#{:code.priv_dir(:message_when_gc)}/message_when_gc"
    case :erlang.load_nif(nif_file, 0) do
      :ok -> :ok
      {:error, {:reload, _}} -> :ok
      {:error, reason} -> IO.puts("Failed to load nif: #{inspect(reason)}")
    end
  end

  def message_when_gc(_pid, _value), do: :erlang.nif_error(:nif_not_loaded)
end
