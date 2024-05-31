defmodule MessageWhenGc.MixProject do
  use Mix.Project

  def project do
    [
      app: :message_when_gc,
      version: "0.1.0",
      elixir: "~> 1.12",
      start_permanent: Mix.env() == :prod,
      deps: deps()
    ]
  end

  def application do
    [
      extra_applications: [:logger]
    ]
  end

  defp deps do
    [
      {:elixir_make, "~> 0.7.0"}
    ]
  end
end
