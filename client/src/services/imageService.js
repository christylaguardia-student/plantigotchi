require('dotenv').config();
const superagent = require('superagent');
const photos = require('./imageurls.json');

export const populateDB = async () => {
  let postResponses = [];
  await photos.map(async photo => {
    photo = {
      title: `${photo.title}`,
      url: `https://www.flickr.com/photos/${photo.owner}/${photo.id}`,
      alt: 'alt text',
      description: 'description'
    };
    const savedImage = await superagent.post('/api/images').send(photo);
    postResponses.push(savedImage.body);
    return postResponses;
  });
  return postResponses;
};

export const AddNewImage = async newPhoto => {
  const savedImage = await superagent.post(`/api/images`).send(newPhoto);
  return savedImage;
};

export const httpTaskCallback = async (target) => {
  console.log('callback: ', target)
  // await superagent.post(`/api/images`)
  //   .send(target)
  //   .end((err, res) => {
  //     if (!err) return this.setState({ ...task })
  //     // Handle HTTP error
  //   })
}



export const DeleteImage = async imageId => {
  const deletedImage = await superagent
    .delete(`/api/images`)
    .query({ _id: imageId });
  return deletedImage;
};
