#include "Framework.h"

unordered_map<wstring, Texture*> Texture::textures;

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image, wstring file)
    : srv(srv), image(move(image)), file(file)
{
}

Texture::~Texture()
{
    srv->Release();
}

void Texture::PSSet(UINT slot)
{
    DC->PSSetShaderResources(slot, 1, &srv);
}

Texture* Texture::Add(wstring file)
{
    if (textures.count(file) > 0)
        return textures[file];

    wstring extension = Utility::GetExtension(file);

    ScratchImage image;
    HRESULT hResult;
    
    if (extension.compare(L"tga") == 0)
        hResult = LoadFromTGAFile(file.c_str(), nullptr, image);
    else if (extension.compare(L"dds") == 0)
        hResult = LoadFromDDSFile(file.c_str(), DDS_FLAGS_NONE, nullptr, image);
    else
        hResult = LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);

    assert(SUCCEEDED(hResult));	

    ID3D11ShaderResourceView* srv;

    CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(),
        image.GetMetadata(), &srv);

    textures[file] = new Texture(srv, image, file);

    return textures[file];
}

Texture* Texture::Add(wstring file, wstring key)
{
    if (textures.count(key) > 0)
        return textures[key];

    wstring extension = Utility::GetExtension(file);

    ScratchImage image;
    HRESULT hResult;

    if (extension.compare(L"tga") == 0)
        hResult = LoadFromTGAFile(file.c_str(), nullptr, image);
    else if (extension.compare(L"dds") == 0)
        hResult = LoadFromDDSFile(file.c_str(), DDS_FLAGS_NONE, nullptr, image);
    else
        hResult = LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);

    assert(SUCCEEDED(hResult));

    ID3D11ShaderResourceView* srv;

    CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(),
        image.GetMetadata(), &srv);

    textures[key] = new Texture(srv, image, file);

    return textures[key];
}

Texture* Texture::Add(wstring key, ID3D11ShaderResourceView* srv)
{
    if (textures.count(key) > 0)
        return textures[key];

    ScratchImage image;

    textures[key] = new Texture(srv, image, key);

    return textures[key];
}

void Texture::Delete()
{
    for (pair<wstring, Texture*> texture : textures)
        delete texture.second;
}
