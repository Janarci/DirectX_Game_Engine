Texture2D Texture: register(t0);
sampler TextureSampler: register(s0);



struct PS_INPUT
{
	float4 position: SV_POSITION;
	float2 texcoord: TEXCOORD0;
};

cbuffer constant: register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_proj;
	unsigned int m_time;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
	float2 xy = 2.0 * input.texcoord.xy - 1;
	float2 uv;
	float d = length(xy);
	float4 color = Texture.Sample(TextureSampler, input.texcoord) * 2;

	if (d<1.0)
	{
		return float4(1, 0, 0, 1) * color;

	}
	else
	{
		return color;
	}

	
}